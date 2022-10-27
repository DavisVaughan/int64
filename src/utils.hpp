#ifndef INT64_UTILS_HPP
#define INT64_UTILS_HPP

namespace pkg {
namespace utils {

// - 19 comes from printing out `INT64_MAX` and counting the number of digits
// - `+ 1` because it could be negative and have a `-`
// - TODO: And `+ 1` for trailing null?
static inline
int
get_int64_max_print_size() {
  return (19 + 1 + 1);
}

}
}

#endif
