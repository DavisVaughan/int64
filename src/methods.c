#include "int64.h"

SEXP int64_is_na(SEXP x) {
  R_xlen_t size = Rf_xlength(x);

  x = R_altrep_data1(x);
  long long* p_x = INT64(x);

  SEXP out = PROTECT(Rf_allocVector(LGLSXP, size));
  int* p_out = LOGICAL(out);

  for (R_xlen_t i = 0; i < size; ++i) {
    p_out[i] = (p_x[i] == NA_INT64);
  }

  UNPROTECT(1);
  return out;
}

// [[ export() ]]
SEXP export_int64_is_na(SEXP x) {
  return int64_is_na(x);
}
