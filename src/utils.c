#include "utils.h"

SEXP int64_ns_env = NULL;

// {{ include("init64.h") }}
void int64_init_utils(SEXP ns) {
  int64_ns_env = ns;
}
