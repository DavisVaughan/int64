#include "int64.h"
#include "utils.h"

static SEXP int64_vec_coercible_cast(SEXP x, SEXP to) {
  // Ensure there is a common type
  int64_vec_ptype2(x, to);

  return int64_vec_cast(x, to);
}

SEXP int64_slice_assign(SEXP x, SEXP i, SEXP value) {
  R_xlen_t x_size = Rf_xlength(x);

  SEXP names = Rf_getAttrib(x, R_NamesSymbol);

  SEXP locs = PROTECT(int64_vec_as_location(i, x_size, names));
  int* p_locs = INTEGER(locs);

  R_xlen_t value_size = Rf_xlength(locs);

  value = PROTECT(int64_vec_coercible_cast(value, x));
  value = PROTECT(int64_vec_recycle(value, value_size));
  long long* p_value = INT64(value);

  SEXP out = PROTECT(Rf_duplicate(x));
  long long* p_out = INT64(out);

  for (R_xlen_t i = 0; i < value_size; ++i) {
    int loc = p_locs[i];

    if (loc == NA_INTEGER) {
      continue;
    }

    p_out[loc - 1] = p_value[i];
  }

  UNPROTECT(4);
  return out;
}

// [[ export() ]]
SEXP export_int64_slice_assign(SEXP x, SEXP i, SEXP value) {
  return int64_slice_assign(x, i, value);
}
