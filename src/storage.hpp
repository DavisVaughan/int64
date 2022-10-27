#ifndef INT64_STORAGE_H
#define INT64_STORAGE_H

#include <rlang.hpp>

namespace pkg {
namespace storage {

/*
 * This pair of functions facilitates:
 * - Splitting an `int64_t` into two `uint32_t` values, maintaining order
 * - Combining those two `uint32_t` values back into the original `int32_t`
 *
 * The two `uint32_t` values are stored in an `r_complex`, where each of the two
 * components are promoted to double. This gives us native performance for most
 * operations, and also allows `NA_real_` to function as the natural candidate
 * for missing values. We can also just promote the complex vector to a two
 * column data frame when a comparison proxy is required.
 *
 * Unsigned 32-bit integers are used because bit shifting is undefined on signed
 * types.
 *
 * An arithmetic shift of `- INT64_MIN` is done to remap the int64_t value
 * into uint64_t space, while maintaining order. This relies on unsigned
 * arithmetic overflow behavior, which is well-defined.
 *
 * Missing values are assumed to be handled outside this function by checking
 * to see if `isnan(x.r)` is true.
 */

static inline
r_complex convert(int64_t x) {
  const uint64_t x_u64 = static_cast<uint64_t>(x) - INT64_MIN;

  const uint32_t left_u32 = static_cast<uint32_t>(x_u64 >> 32);
  const uint32_t right_u32 = static_cast<uint32_t>(x_u64);

  const r_complex out = {
    .r = static_cast<double>(left_u32),
    .i = static_cast<double>(right_u32)
  };

  return out;
}

static inline
int64_t convert(r_complex x) {
  const uint32_t left_u32 = static_cast<uint32_t>(x.r);
  const uint32_t right_u32 = static_cast<uint32_t>(x.i);

  const uint64_t out_u64 = static_cast<uint64_t>(left_u32) << 32 | right_u32;

  const int64_t out = static_cast<int64_t>(out_u64 + INT64_MIN);

  return out;
}

};
};

#endif
