#include "int64.h"

// - Assume x is integer

// Quick benchmarks show that this is MUCH slower than using a raw vector
// to hold the entire long long array

// [[ export() ]]
SEXP as_int64_list(SEXP x) {
  R_xlen_t size = Rf_xlength(x);

  int* p_x = INTEGER(x);

  SEXP out = PROTECT(Rf_allocVector(VECSXP, size));

  for (R_xlen_t i = 0; i < size; ++i) {
    int x_elt = p_x[i];

    if (x_elt == NA_INTEGER) {
      SET_VECTOR_ELT(out, i, R_NilValue);
      continue;
    }

    SEXP out_elt = PROTECT(Rf_allocVector(RAWSXP, sizeof(long long)));
    long long* p_out_elt = (long long*) RAW(out_elt);

    p_out_elt[0] = (long long) x_elt;

    SET_VECTOR_ELT(out, i, out_elt);

    UNPROTECT(1);
  }

  UNPROTECT(1);
  return out;
}
