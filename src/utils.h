#ifndef INT64_UTILS_H
#define INT64_UTILS_H

// - 19 comes from printing out `INT64_MAX` and counting the number of digits
// - `+ 1` because it could be negative and have a `-`
// - TODO: And `+ 1` for trailing null?
#define INT64_MAX_PRINT_SIZE (19 + 1 + 1)

#endif
