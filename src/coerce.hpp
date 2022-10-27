#ifndef INT64_COERCE_HPP
#define INT64_COERCE_HPP

#include <rlang.hpp>

namespace pkg {

r_obj* coerce_int_to_int64(r_obj* x);

r_obj* coerce_int64_to_int(r_obj* x);
r_obj* coerce_int64_to_chr(r_obj* x);

} // namespace pkg

#endif
