#include "checks.hpp"
#include "coerce.hpp"
#include "storage.hpp"
#include <rlang.hpp>

namespace pkg {
namespace cast {

r_obj* int_to_int64(r_obj* x) {
  return pkg::coerce::int_to_int64(x);
}

r_obj* int64_to_int(r_obj* x) {
  return pkg::coerce::int64_to_int(x);
}

}

namespace ffi {

r_obj* cast_int_to_int64(r_obj* x) {
  return pkg::cast::int_to_int64(x);
}

r_obj* cast_int64_to_int(r_obj* x) {
  return pkg::cast::int64_to_int(x);
}

}
}
