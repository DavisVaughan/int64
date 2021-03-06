#include "int64.h"

// - 19 comes from printing out `LLONG_MAX`
//   and counting the number of digits
// - `+ 1` because it could be negative and have a `-`
// - And `+ 1` for trailing null thing?
#define MAX_INT64_ELT_SIZE (19 + 1 + 1)

SEXP format_int64(SEXP x) {
  long long* p_x =  INT64(x);

  R_xlen_t size = Rf_xlength(x);

  SEXP out = PROTECT(Rf_allocVector(STRSXP, size));
  SEXP* p_out_chr = STRING_PTR(out);

  char buf[MAX_INT64_ELT_SIZE];

  for (R_xlen_t i = 0; i < size; ++i) {
    long long elt = p_x[i];

    if (elt == NA_INT64) {
      p_out_chr[i] = NA_STRING;
      continue;
    }

    snprintf(buf, MAX_INT64_ELT_SIZE, "%lli", p_x[i]);

    p_out_chr[i] = Rf_mkChar(buf);
  }

  UNPROTECT(1);
  return out;
}

// [[ export() ]]
SEXP export_format_int64(SEXP x) {
  return format_int64(x);
}
