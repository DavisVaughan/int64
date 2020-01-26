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

#define INT64(x) ((long long*) DATAPTR(x))
#define INT64_RO(x) ((const long long*) DATAPTR_RO(x))

// TODO is this right?
#define NA_INT64 LONG_LONG_MIN

#endif
