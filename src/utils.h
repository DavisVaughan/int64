#ifndef UTILS_H
#define UTILS_H

#include "r.h"

// --------------------------------------------------------------
// Variables

extern SEXP int64_ns_env;

// --------------------------------------------------------------
// Functions

SEXP r_quote(SEXP x);
SEXP r_maybe_duplicate(SEXP x);

void new_int64(SEXP x);

SEXP int64_vec_as_location(SEXP x, R_xlen_t n, SEXP names);
SEXP int64_vec_cast(SEXP x, SEXP to);
SEXP int64_vec_ptype2(SEXP x, SEXP y);
SEXP int64_vec_recycle(SEXP x, R_xlen_t size);
SEXP int64_vec_slice(SEXP x, SEXP i);

#endif
