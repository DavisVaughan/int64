#ifndef INT64_STORAGE_H
#define INT64_STORAGE_H

#include <rlang.h>

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
 */

static inline
r_complex int64_to_cpl(int64_t x) {
  const uint64_t x_u64 = ((uint64_t) x) - INT64_MIN;

  const uint32_t left_u32 = (uint32_t) (x_u64 >> 32);
  const uint32_t right_u32 = (uint32_t) x_u64;

  const r_complex out = {
    .r = (double) left_u32,
    .i = (double) right_u32
  };

  return out;
}

static inline
int64_t int64_to_int64(r_complex x) {
  const uint32_t left_u32 = (uint32_t) x.r;
  const uint32_t right_u32 = (uint32_t) x.i;

  const uint64_t out_u64 = ((uint64_t) left_u32) << 32 | right_u32;

  const int64_t out = (int64_t) (out_u64 + INT64_MIN);

  return out;
}

#endif
