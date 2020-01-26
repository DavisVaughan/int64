#ifndef ALTREP_INT64_UTIL_H
#define ALTREP_INT64_UTIL_H

#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <stdbool.h>
#include <R_ext/Altrep.h>

// --------------------------------------------------------------
// Utilities

// Initialized in `init_altrep_int64()` at load time
static R_altrep_class_t altrep_int64_class_t;

// --------------------------------------------------------------

#endif
