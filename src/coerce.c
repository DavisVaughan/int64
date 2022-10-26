#include "coerce.h"
#include "storage.h"
#include "utils.h"

// For PRId64
#include <inttypes.h>

r_obj* ffi_coerce_int64_to_chr(r_obj* x) {
  r_ssize size = r_length(x);
  const r_complex* v_x = r_cpl_cbegin(x);

  r_obj* out = KEEP(r_alloc_character(size));
  r_attrib_poke_names(out, r_names(x));

  char out_elt[INT64_MAX_PRINT_SIZE];

  for (r_ssize i = 0; i < size; ++i) {
    const r_complex x_elt = v_x[i];

    if (isnan(x_elt.r)) {
      r_chr_poke(out, i, r_globals.na_str);
      continue;
    }

    const int64_t elt = int64_to_int64(x_elt);

    snprintf(out_elt, INT64_MAX_PRINT_SIZE, "%" PRId64, elt);

    r_chr_poke(out, i, r_str(out_elt));
  }

  FREE(1);
  return out;
}
