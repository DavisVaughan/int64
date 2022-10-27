#include "checks.hpp"
#include "coerce.hpp"
#include "storage.hpp"
#include <rlang.hpp>

namespace pkg {

r_obj* cast_int_to_int64(r_obj* x) {
  return coerce_int_to_int64(x);
}

namespace ffi {
r_obj* cast_int_to_int64(r_obj* x) {
  return pkg::cast_int_to_int64(x);
}
} // namespace ffi

r_obj* cast_int64_to_int(r_obj* x) {
  return coerce_int64_to_int(x);
}

namespace ffi {
r_obj* cast_int64_to_int(r_obj* x) {
  return pkg::cast_int64_to_int(x);
}
} // namespace ffi

} // namespace pkg
