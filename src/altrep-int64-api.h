#ifndef ALTREP_INT64_API_H
#define ALTREP_INT64_API_H

// --------------------------------------------------------------
// API

SEXP new_altrep_int64(SEXP x);
SEXP altrep_int64_alloc(R_xlen_t n);
bool is_altrep_int64(SEXP x);

// --------------------------------------------------------------

#endif
