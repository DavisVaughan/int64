#include "conditions.hpp"
#include "globals.hpp"

namespace pkg {
namespace conditions {

void signal_oob_int64_to_int(r_ssize i) {
  r_obj* ffi_call = KEEP(r_sym("signal_oob_int64_to_int"));
  r_obj* ffi_i = KEEP(r_int(i + 1));

  r_obj* call = KEEP(r_call2(ffi_call, ffi_i));
  r_eval(call, pkg::globals::envs::int64);

  FREE(3);
}

}
}
