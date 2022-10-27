#include "globals.hpp"

namespace pkg {

r_obj* envs::int64 = NULL;

r_obj* classes::int64 = NULL;

int limits::r_max_int = INT_MAX;
int limits::r_min_int = INT_MIN + 1;

int64_t limits::max_int64 = INT64_MAX;
int64_t limits::min_int64 = INT64_MIN;

// We need to prevent overflow when converting a double to an int64_t, so we
// need to be able to detect that we are over the max allowed double value.
// If INT64_MAX was used, which is 2^63-1, then we cannot detect overflow when
// a double of 2^63 is given because they look identical. Instead we use the
// next lowest value that is detectable as a double. The spacing between
// representable numbers in the range of [2^n, 2^(n+1)] is 2^(n-52). This means
// we are in the range of [2^62, 2^(62+1)], the spacing is 2^(62-52) = 1024, and
// the next lowest detectable double before INT64_MAX is
// 2^63 - 1024 = 9223372036854774784.
double limits::max_dbl_to_int64 = 9223372036854774784.0;
double limits::min_dbl_to_int64 = -limits::max_dbl_to_int64;

// Maximum int64_t value such that it and all smaller integers can be represented
// in a double loss of precision. It is 2^53.
// https://stackoverflow.com/questions/1848700/biggest-integer-that-can-be-stored-in-a-double
int64_t limits::max_no_precision_loss_int64_to_dbl = 9007199254740992;
int64_t limits::min_no_precision_loss_int64_to_dbl = -limits::max_no_precision_loss_int64_to_dbl;

// - 19 comes from printing out `INT64_MAX` and counting the number of digits
// - `+ 1` because it could be negative and have a `-`
// - TODO: And `+ 1` for trailing null?
int values::max_print_size_int64 = (19 + 1 + 1);

namespace ffi {
void init_library_globals(r_obj* ns) {
  envs::int64 = ns;

  const char* v_int64_class[] = { "int64_int64", "vctrs_vctr" };
  classes::int64 = r_chr_n(v_int64_class, R_ARR_SIZEOF(v_int64_class));
  r_preserve_global(classes::int64);
}
} // namespace ffi

} // namespace pkg
