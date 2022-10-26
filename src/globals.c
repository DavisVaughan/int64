#include "globals.h"

struct int64_globals_classes int64_classes;

void int64_init_library_globals(r_obj* ns) {
  const char* v_int64_class[] = { "int64_int64", "vctrs_vctr" };
  int64_classes.int64 = r_chr_n(v_int64_class, R_ARR_SIZEOF(v_int64_class));
  r_preserve_global(int64_classes.int64);
}
