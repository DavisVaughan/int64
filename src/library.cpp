#include <rlang.hpp>

namespace pkg {
namespace ffi {

extern void init_library_globals(r_obj* ns);

r_obj* init_library(r_obj* ns) {
  r_init_library(ns);
  init_library_globals(ns);
  return r_null;
}

} // namespace ffi
} // namespace pkg
