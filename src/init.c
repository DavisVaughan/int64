#include <rlang.h>
#include <R_ext/Rdynload.h>

// Compile with `-fvisibility=hidden -DHAVE_VISIBILITY_ATTRIBUTE` if you link to this library
#include <R_ext/Visibility.h>
#define export attribute_visible extern

r_obj* ffi_init_library(r_obj* ns);

extern r_obj* ffi_cast_int_to_int64(r_obj*);
extern r_obj* ffi_coerce_int64_to_chr(r_obj* x);

static const R_CallMethodDef CallEntries[] = {
  {"ffi_init_library", (DL_FUNC) &ffi_init_library, 1},
  {"ffi_cast_int_to_int64", (DL_FUNC) &ffi_cast_int_to_int64, 1},
  {"ffi_coerce_int64_to_chr", (DL_FUNC) &ffi_coerce_int64_to_chr, 1},
  {NULL, NULL, 0}
};

export void R_init_int64(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}

extern void int64_init_library_globals(r_obj* ns);

r_obj* ffi_init_library(r_obj* ns) {
  r_init_library(ns);
  int64_init_library_globals(ns);
  return r_null;
}
