#include "int64.h"

// [[ export() ]]
SEXP export_int64_init_library(SEXP ns) {
  int64_init_utils(ns);

  return R_NilValue;
}
