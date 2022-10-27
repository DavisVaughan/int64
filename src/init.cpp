#include <rlang.hpp>
#include <R_ext/Rdynload.h>

// Compile with `-fvisibility=hidden -DHAVE_VISIBILITY_ATTRIBUTE` if you link to this library
#include <R_ext/Visibility.h>
#define export attribute_visible extern

namespace pkg {
namespace ffi {

extern r_obj* init_library(r_obj*);
extern r_obj* cast_int_to_int64(r_obj*);
extern r_obj* cast_int64_to_int(r_obj*);
extern r_obj* coerce_int_to_int64(r_obj*);
extern r_obj* coerce_int64_to_int(r_obj*);
extern r_obj* coerce_int64_to_chr(r_obj*);

} // namespace ffi
} // namespace pkg

extern "C" {

static const R_CallMethodDef CallEntries[] = {
  {"ffi_init_library", (DL_FUNC) &pkg::ffi::init_library, 1},
  {"ffi_cast_int_to_int64", (DL_FUNC) &pkg::ffi::cast_int_to_int64, 1},
  {"ffi_cast_int64_to_int", (DL_FUNC) &pkg::ffi::cast_int64_to_int, 1},
  {"ffi_coerce_int_to_int64", (DL_FUNC) &pkg::ffi::coerce_int_to_int64, 1},
  {"ffi_coerce_int64_to_int", (DL_FUNC) &pkg::ffi::coerce_int64_to_int, 1},
  {"ffi_coerce_int64_to_chr", (DL_FUNC) &pkg::ffi::coerce_int64_to_chr, 1},
  {NULL, NULL, 0}
};

export void R_init_int64(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}

} // extern "C"
