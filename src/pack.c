#include "int64.h"
#include "utils.h"
#include <inttypes.h>

/*
 * Unpack a int64 vector into a data frame of two double vectors that encode
 * all of the int64 information with no loss of precision, all while maintaining
 * ordering.
 *
 * The idea is to take a 64-bit long long value and split it into two 32-bit
 * parts, the `first` 32 bits and the `last` 32 bits.
 *
 * The `first` 32-bits are converted as follows:
 * - To an `int`
 * - Then to an `unsigned int`
 * - Then to a `double`
 *
 * The `last` 32-bits are converted as follows:
 * - To an `int`
 * - Then to a `double`
 *
 * The reason we do it this way is to maintain ordering, so it can serve as a
 * proxy for usage with `vec_order()` / `vec_sort()` and `vec_compare()`.
 *
 * The range of `first` is: [0, 4294967295]
 * The range of `last` is: [-2147483648, 2147483647]
 *
 * The integer values in both of these ranges are representable as doubles
 * with no loss of precision (you start to lose precision with integer values
 * at 2^53 + 1).
 *
 * There are two reasons we have to use double vectors as containers. The first
 * is that `NA_integer_` is represented in R as the smallest int value,
 * `-2147483648`, but this value has an important meaning if it is assigned
 * to `last`. It needs to not be NA. The second is more straightforward. We
 * have to assign an unsigned int to an R object. The only one that can hold
 * that range is a double.
 *
 * Order is maintained by first looking at the value of `last`, which
 * represents the number of complete unsigned int ranges to shift by. If
 * the values are equal, then we look to the value of `first`, which is value
 * within the current unsigned int range.
 *
 * For example:
 * int64_unpack(as_int64(c(-1, 0, 1)))
 *   last      first
 * 1   -1 4294967295
 * 2    0          0
 * 3    0          1
 */

// Map `elt_first` into unsigned int range
// This is essentially what the following cast would do
// based on 6.3.1.3 of the C99 standard
// (double) (unsigned int) elt_first
// "Otherwise, if the new type is unsigned, the value is converted by
// repeatedly adding or subtracting one more than the maximum value that
// can be represented in the new type until the value is in the range of
// the new type"
// http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf

static SEXP new_unpacked_data_frame(R_len_t size);

// [[ export() ]]
SEXP export_int64_unpack(SEXP x) {
  int64_t* p_x = INT64(x);

  R_xlen_t size = Rf_xlength(x);

  SEXP first = PROTECT(Rf_allocVector(REALSXP, size));
  double* p_first = REAL(first);

  SEXP last = PROTECT(Rf_allocVector(REALSXP, size));
  double* p_last = REAL(last);

  for (R_xlen_t i = 0; i < size; ++i) {
    int64_t elt = p_x[i];

    if (elt == NA_INT64) {
      p_first[i] = NA_REAL;
      p_last[i] = NA_REAL;
      continue;
    }

    // Map long long into unsigned long long range
    // Bit shifts are only well defined on unsigned values

    uint64_t elt_ull;
    if (signbit(elt)) {
      elt_ull = (uint64_t) (elt + 1 + LLONG_MAX) - LLONG_MIN;
    } else {
      elt_ull = (uint64_t) elt;
    }

    // Bit shift to separate into two chunks of 32 bits
    // (I think this isn't specific to any endianness)
    uint32_t elt_first = (uint32_t) (elt_ull & 0xFFFFFFFFLL);
    uint32_t elt_last = (uint32_t) (elt_ull >> 32);

    // Map unsigned int into int range, then convert to double
    int32_t elt_last_int;
    if (elt_last > INT32_MAX) {
      elt_last_int = ((int32_t) (elt_last - 1 - INT32_MAX) + INT32_MIN);
    } else {
      elt_last_int = elt_last;
    }

    p_first[i] = (double) elt_first;
    p_last[i] = (double) elt_last_int;
  }

  SEXP out = PROTECT(new_unpacked_data_frame(size));

  SET_VECTOR_ELT(out, 0, last);
  SET_VECTOR_ELT(out, 1, first);

  UNPROTECT(3);
  return out;
}

// [[ export() ]]
SEXP export_int64_pack(SEXP x) {
  SEXP last = VECTOR_ELT(x, 0);
  double* p_last = REAL(last);

  SEXP first = VECTOR_ELT(x, 1);
  double* p_first = REAL(first);

  R_xlen_t size = Rf_xlength(first);

  SEXP out = PROTECT(altrep_int64_alloc(size));
  new_int64(out);
  int64_t* p_out = INT64(out);

  for (R_xlen_t i = 0; i < size; ++i) {
    double elt_first = p_first[i];
    double elt_last = p_last[i];

    // Only need to check one
    if (elt_first == NA_REAL) {
      p_out[i] = NA_INT64;
      continue;
    }

    // Always positive, easy
    uint32_t elt_first_u32 = (uint32_t) elt_first;

    // Always representable in an int
    int elt_last_int = (int) elt_last;

    // Map from int to unsigned int range
    uint32_t elt_last_u32;
    if (signbit(elt_last_int)) {
      elt_last_u32 = (uint32_t) (elt_last_int + 1 + INT_MAX) - INT_MIN;
    } else {
      elt_last_u32 = (uint32_t) elt_last_int;
    }

    // Reconstruct unsigned long long
    uint64_t elt_ull = ((uint64_t) elt_last_u32) << 32 | elt_first_u32;

    // Map unsigned long long to long long range
    int64_t elt;
    if (elt_ull > LLONG_MAX) {
      elt = (int64_t) (elt_ull - 1 - LLONG_MAX) + LLONG_MIN;
    } else {
      elt = (int64_t) elt_ull;
    }

    p_out[i] = elt;
  }

  UNPROTECT(1);
  return out;
}

// -----------------------------------------------------------------------------

static SEXP new_row_name_info(R_len_t size) {
  SEXP out = PROTECT(Rf_allocVector(INTSXP, 2));
  int* p_out = INTEGER(out);

  p_out[0] = NA_INTEGER;
  p_out[1] = -size;

  UNPROTECT(1);
  return out;
}

static SEXP new_unpacked_data_frame(R_len_t size) {
  SEXP out = PROTECT(Rf_allocVector(VECSXP, 2));

  SEXP strings_last_first = PROTECT(Rf_allocVector(STRSXP, 2));
  SET_STRING_ELT(strings_last_first, 0, Rf_mkChar("last"));
  SET_STRING_ELT(strings_last_first, 1, Rf_mkChar("first"));

  SEXP classes_data_frame = PROTECT(Rf_allocVector(STRSXP, 1));
  SET_STRING_ELT(classes_data_frame, 0, Rf_mkChar("data.frame"));

  Rf_setAttrib(out, R_NamesSymbol, strings_last_first);
  Rf_setAttrib(out, R_ClassSymbol, classes_data_frame);
  Rf_setAttrib(out, R_RowNamesSymbol, new_row_name_info(size));

  UNPROTECT(3);
  return out;
}
