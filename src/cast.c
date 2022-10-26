#include "storage.h"
#include "globals.h"
#include <rlang.h>

r_obj* ffi_cast_int_to_int64(r_obj* x) {
  r_ssize size = r_length(x);
  const int* v_x = r_int_cbegin(x);

  r_obj* out = KEEP(r_alloc_complex(size));
  r_complex* v_out = r_cpl_begin(out);
  r_attrib_poke_class(out, int64_classes.int64);
  r_attrib_poke_names(out, r_names(x));

  for (r_ssize i = 0; i < size; ++i) {
    const int x_elt = v_x[i];

    if (x_elt == r_globals.na_int) {
      v_out[i] = r_globals.na_cpl;
      continue;
    }

    const int64_t elt = (int64_t) x_elt;
    v_out[i] = int64_to_cpl(elt);
  }

  FREE(1);
  return out;
}
