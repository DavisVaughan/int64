#ifndef INT64_H
#define INT64_H

#define R_NO_REMAP
#include <R.h>
#include <Rversion.h>
#include <Rinternals.h>
#include <stdbool.h>

#include "altrep-int64-api.h"

// --------------------------------------------------------------
// API

#define INTEGER64(x) ((long long*) DATAPTR(x))
#define INTEGER64_RO(x) ((const long long*) DATAPTR_RO(x))

// --------------------------------------------------------------
// Compatibility

#if (R_VERSION < R_Version(3, 5, 0))
  #define LOGICAL_RO(x) ((const int*) LOGICAL(x))
  #define INTEGER_RO(x) ((const int*) INTEGER(x))
  #define REAL_RO(x) ((const double*) REAL(x))
  #define COMPLEX_RO(x) ((const Rcomplex*) COMPLEX(x))
  #define STRING_PTR_RO(x) ((const SEXP*) STRING_PTR(x))
  #define RAW_RO(x) ((const Rbyte*) RAW(x))
#endif

#endif
