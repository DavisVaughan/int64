#ifndef INT64_GLOBALS_HPP
#define INT64_GLOBALS_HPP

#include <rlang.hpp>

namespace pkg {

struct envs {
  static r_obj* int64;
};

struct classes {
  static r_obj* int64;
};

struct limits {
  static int r_max_int;
  static int r_min_int;

  static int64_t max_int64;
  static int64_t min_int64;

  static double max_dbl_to_int64;
  static double min_dbl_to_int64;

  static int64_t max_no_precision_loss_int64_to_dbl;
  static int64_t min_no_precision_loss_int64_to_dbl;
};

struct values {
  static int max_print_size_int64;
};

} // namespace pkg

#endif
