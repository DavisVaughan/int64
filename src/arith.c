#include "int64.h"
#include "utils.h"

/* borrowed from R (arithmetic.c) */
// #define OPPOSITE_SIGNS(x, y) ((x < 0) ^ (y < 0))
#define NO_SUM_OVERFLOW(x, y, z) (((x) > 0) ? ((y) < (z)) : ! ((y) < (z)))
// #define NO_DIFF_OVERFLOW(x, y, z) (!(OPPOSITE_SIGNS(x, y) && OPPOSITE_SIGNS(x, z)))
// #define NO_PROD_OVERFLOW(x, y, z) ((long double) (x) * (long double) (y) == (z))

// [[ export() ]]
SEXP export_int64_int64_plus(SEXP x, SEXP y) {
  const long long* p_x = INT64(x);
  const long long* p_y = INT64(y);

  // Assumes sizes are the same, checked at R level
  R_xlen_t size = Rf_xlength(x);

  SEXP out = PROTECT(altrep_int64_alloc(size));
  long long* p_out = INT64(out);

  for (R_xlen_t i = 0; i < size; ++i) {
    const long long x_elt = p_x[i];
    const long long y_elt = p_y[i];

    if (x_elt == NA_INT64 || y_elt == NA_INT64) {
      p_out[i] = NA_INT64;
      continue;
    }

    const long long out_elt = x_elt + y_elt;

    // for example) as_int64("-9223372036854775807") + as_int64(-1)
    if (out_elt == NA_INT64) {
      // TODO - throw overflow warning
      p_out[i] = NA_INT64;
      continue;
    }

    if (NO_SUM_OVERFLOW(x_elt, y_elt, out_elt)) {
      p_out[i] = out_elt;
    } else {
      // TODO - throw overflow warning
      p_out[i] = NA_INT64;
    }
  }

  // TODO - improve me to be no copy
  out = PROTECT(new_int64(out));

  UNPROTECT(2);
  return out;
}
