#ifndef INT64_COERCE_HPP
#define INT64_COERCE_HPP

#include <rlang.hpp>

namespace pkg {
namespace coerce {

r_obj* int_to_int64(r_obj* x);

r_obj* int64_to_int(r_obj* x);
r_obj* int64_to_chr(r_obj* x);

}
}

#endif
