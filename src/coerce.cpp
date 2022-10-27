#include "checks.hpp"
#include "coerce.hpp"
#include "conditions.hpp"
#include "globals.hpp"
#include "storage.hpp"

// For PRId64
#include <inttypes.h>

namespace pkg {

r_obj* coerce_int_to_int64(r_obj* x) {
  const r_ssize size = r_length(x);
  const int* v_x = r_int_cbegin(x);

  r_obj* out = KEEP(r_alloc_complex(size));
  r_complex* v_out = r_cpl_begin(out);
  r_attrib_poke_class(out, classes::int64);
  r_attrib_poke_names(out, r_names(x));

  for (r_ssize i = 0; i < size; ++i) {
    const int x_elt = v_x[i];

    if (x_elt == r_globals.na_int) {
      v_out[i] = r_globals.na_cpl;
      continue;
    }

    const int64_t elt = static_cast<int64_t>(x_elt);
    v_out[i] = convert(elt);
  }

  FREE(1);
  return out;
}

namespace ffi {
r_obj* coerce_int_to_int64(r_obj* x) {
  return pkg::coerce_int_to_int64(x);
}
} // namespace ffi

r_obj* coerce_int64_to_int(r_obj* x) {
  const r_ssize size = r_length(x);
  const r_complex* v_x = r_cpl_cbegin(x);

  r_obj* out = KEEP(r_alloc_integer(size));
  int* v_out = r_int_begin(out);
  r_attrib_poke_names(out, r_names(x));

  bool signal = true;

  for (r_ssize i = 0; i < size; ++i) {
    const r_complex x_elt = v_x[i];

    if (isnan(x_elt.r)) {
      v_out[i] = r_globals.na_int;
      continue;
    }

    const int64_t elt = convert(x_elt);

    if (is_oob_int64_to_int(elt)) {
      if (signal) {
        signal = false;
        signal_oob_int64_to_int(i);
      }

      v_out[i] = r_globals.na_int;
      continue;
    }

    v_out[i] = static_cast<int>(elt);
  }

  FREE(1);
  return out;
}

namespace ffi {
r_obj* coerce_int64_to_int(r_obj* x) {
  return pkg::coerce_int64_to_int(x);
}
} // namespace ffi

r_obj* coerce_int64_to_chr(r_obj* x) {
  const r_ssize size = r_length(x);
  const r_complex* v_x = r_cpl_cbegin(x);

  r_obj* out = KEEP(r_alloc_character(size));
  r_attrib_poke_names(out, r_names(x));

  char out_elt[values::max_print_size_int64];

  for (r_ssize i = 0; i < size; ++i) {
    const r_complex x_elt = v_x[i];

    if (isnan(x_elt.r)) {
      r_chr_poke(out, i, r_globals.na_str);
      continue;
    }

    const int64_t elt = convert(x_elt);

    snprintf(out_elt, values::max_print_size_int64, "%" PRId64, elt);

    r_chr_poke(out, i, r_str(out_elt));
  }

  FREE(1);
  return out;
}

namespace ffi {
r_obj* coerce_int64_to_chr(r_obj* x) {
  return pkg::coerce_int64_to_chr(x);
}
} // namespace ffi

} // namespace pkg
