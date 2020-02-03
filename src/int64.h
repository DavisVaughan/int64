#ifndef INT64_H
#define INT64_H

#include "r.h"
#include "altrep-int64-api.h"

// --------------------------------------------------------------
// API

#define INT64(x) ((long long*) DATAPTR(x))
#define INT64_RO(x) ((const long long*) DATAPTR_RO(x))

// - This seems to be what base R does.
// - -2147483648 is the smallest integer, and 2147483647 is the largest, so they
//   just use the smallest integer as NA_integer_.
// - We do something similar, -9223372036854775808 is the smallest long long
//   value and 9223372036854775807 is the largest. We just use the smallest as
//   NA_INT64.
#define NA_INT64 LLONG_MIN


SEXP int64_subset(SEXP x, SEXP subscript);

// --------------------------------------------------------------
// Library initializers

void int64_init_utils(SEXP ns);

#endif
