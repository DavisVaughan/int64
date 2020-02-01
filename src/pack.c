#include "int64.h"
#include "utils.h"
#include <inttypes.h>

/*
 * Unpack a (long long) into two (int) values. This only relies on the standard
 * assumption that a (long long) is twice as many bytes as a (int). A
 * (long long) generally has 8, and an (int) is generally 4.
 */

// [[ export() ]]
SEXP int64_unpack(SEXP x) {
  long long* p_x = INT64(x);

  R_xlen_t size = Rf_xlength(x);

  SEXP first = PROTECT(Rf_allocVector(INTSXP, size));
  int* p_first = INTEGER(first);

  SEXP last = PROTECT(Rf_allocVector(INTSXP, size));
  int* p_last = INTEGER(last);

  for (R_xlen_t i = 0; i < size; ++i) {
    long long elt = p_x[i];

    if (elt == NA_INT64) {
      p_first[i] = NA_INTEGER;
      p_last[i] = NA_INTEGER;
      continue;
    }

    // Split by accessing 32 bits at a time
    int* p_elt_32 = (int*) &elt;

    p_first[i] = p_elt_32[0];
    p_last[i] = p_elt_32[1];
  }

  SEXP out = PROTECT(Rf_allocVector(VECSXP, 2));

  SET_VECTOR_ELT(out, 0, first);
  SET_VECTOR_ELT(out, 1, last);

  UNPROTECT(3);
  return out;
}

/*
 * Pack two (int) values into a single (long long) value.
 *
 * The NA check must check both first and last
 * .Call(int64_unpack, as_int64("2147483648"))
 * will correctly give an int representation of
 * `first=NA_integer_, last=0`
 * but this will be a problem if we only check first
 * The result is only ever NA if both are NA
 */

// [[ export() ]]
SEXP int64_pack(SEXP x) {
  SEXP first = VECTOR_ELT(x, 0);
  int* p_first = INTEGER(first);

  SEXP last = VECTOR_ELT(x, 1);
  int* p_last = INTEGER(last);

  R_xlen_t size = Rf_xlength(first);

  SEXP out = PROTECT(altrep_int64_alloc(size));
  long long* p_out_64 = INT64(out);
  int* p_out_32 = (int*) p_out_64;

  for (R_xlen_t i = 0; i < size; ++i) {
    int elt_first = p_first[i];
    int elt_last = p_last[i];

    if (elt_first == NA_INTEGER && elt_last == NA_INTEGER) {
      p_out_64[i] = NA_INT64;
      continue;
    }

    int loc = i * 2;

    p_out_32[loc] = elt_first;
    p_out_32[loc + 1] = elt_last;
  }

  out = PROTECT(new_int64(out));

  UNPROTECT(2);
  return out;
}
