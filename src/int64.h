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

#endif
