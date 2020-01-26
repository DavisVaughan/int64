#include "int64.h"

// [[ export() ]]
SEXP new_empty_int64() {
  long long x = 0;
  int n = 2;

  SEXP out = PROTECT(altrep_int64_alloc(n));
  long long* p_out = INTEGER64(out);

  p_out[0] = (long long) 1;
  p_out[1] = (long long) 1;

  UNPROTECT(1);
  return out;
}
