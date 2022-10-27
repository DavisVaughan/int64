#ifndef INT64_CHECKS_H
#define INT64_CHECKS_H

#include "globals.hpp"
#include <rlang.hpp>

namespace pkg {

namespace detail {

template <typename T>
static inline
bool
is_oob(T x, T min, T max) {
  return (x < min || x > max);
}

} // namespace detail

static inline
bool
is_oob_int64_to_int(int64_t x) {
  static int64_t r_min_int_64 = static_cast<int64_t>(limits::r_min_int);
  static int64_t r_max_int_64 = static_cast<int64_t>(limits::r_max_int);
  return detail::is_oob(x, r_min_int_64, r_max_int_64);
}

static inline
bool
is_oob_dbl_to_int64(double x) {
  return detail::is_oob(x, limits::min_dbl_to_int64, limits::max_dbl_to_int64);
}

} // namespace pkg

#endif
