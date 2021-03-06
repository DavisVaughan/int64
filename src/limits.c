#include "int64.h"
#include "utils.h"
#include <inttypes.h>

// [[ export() ]]
SEXP export_max_unsigned_int() {
  return Rf_ScalarReal(UINT_MAX);
}

// [[ export() ]]
SEXP export_max_int64() {
  SEXP out = PROTECT(altrep_int64_alloc(1));
  new_int64(out);

  INT64(out)[0] = LLONG_MAX;

  UNPROTECT(1);
  return out;
}

// [[ export() ]]
SEXP export_min_int64() {
  SEXP out = PROTECT(altrep_int64_alloc(1));
  new_int64(out);

  INT64(out)[0] = LLONG_MIN + 1;

  UNPROTECT(1);
  return out;
}
