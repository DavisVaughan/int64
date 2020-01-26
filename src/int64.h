#ifndef INT64_H
#define INT64_H

#include "r.h"
#include "altrep-int64-api.h"

// --------------------------------------------------------------
// API

#define INT64(x) ((long long*) DATAPTR(x))
#define INT64_RO(x) ((const long long*) DATAPTR_RO(x))

// TODO is this right?
#define NA_INT64 LONG_LONG_MIN

// --------------------------------------------------------------
// Library initializers

void int64_init_utils(SEXP ns);

#endif
