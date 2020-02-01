#include "utils.h"

/*
 * Add int64 attributes onto a ALTREP int64 constructed with
 * `altrep_int64_alloc()` or `new_altrep_int64()`
 */

// {{ include("utils.h") }}
void new_int64(SEXP x) {
  SEXP classes_int64 = PROTECT(Rf_allocVector(STRSXP, 2));
  SET_STRING_ELT(classes_int64, 0, Rf_mkChar("int64"));
  SET_STRING_ELT(classes_int64, 1, Rf_mkChar("vctrs_vctr"));

  Rf_setAttrib(x, R_ClassSymbol, classes_int64);

  UNPROTECT(1);
}
