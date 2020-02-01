#include "int64.h"
#include "utils.h"

static SEXP int64_vector_subset(SEXP x, SEXP subscript);

// {{ include("int64.h") }}
SEXP int64_subset(SEXP x, SEXP subscript) {
  SEXP dim = Rf_getAttrib(x, R_DimSymbol);

  if (dim != R_NilValue) {
    Rf_errorcall(R_NilValue, "Array subsetting is not currently supported.");
  }

  return int64_vector_subset(x, subscript);
}

// [[ export() ]]
SEXP export_int64_subset(SEXP x, SEXP subscript) {
  return int64_subset(x, subscript);
}

// -----------------------------------------------------------------------------

static void repair_na_names(SEXP names, SEXP subscript);

static SEXP int64_vector_subset(SEXP x, SEXP subscript) {
  R_xlen_t x_size = Rf_xlength(x);

  SEXP names = Rf_getAttrib(x, R_NamesSymbol);

  SEXP locs = PROTECT(int64_vec_as_location(subscript, x_size, names));
  int* p_locs = INTEGER(locs);

  R_xlen_t out_size = Rf_xlength(locs);

  SEXP data1 = R_altrep_data1(x);
  long long* p_data1 = INT64(data1);

  SEXP out = PROTECT(altrep_int64_alloc(out_size));
  new_int64(out);
  long long* p_out = INT64(out);

  for (R_xlen_t i = 0; i < out_size; ++i) {
    int loc = p_locs[i];

    if (loc == NA_INTEGER) {
      p_out[i] = NA_INT64;
      continue;
    }

    // R -> C based
    --loc;

    p_out[i] = p_data1[loc];
  }

  if (names != R_NilValue) {
    names = PROTECT(int64_vec_slice(names, locs));
    repair_na_names(names, locs);
    Rf_setAttrib(out, R_NamesSymbol, names);
    UNPROTECT(1);
  }

  UNPROTECT(2);
  return out;
}


// Replace any `NA` name caused by `NA` subscript with the empty
// string. It's ok mutate the names vector since it is freshly
// created, but we make an additional check for that anyways
static void repair_na_names(SEXP names, SEXP locations) {
  if (!NO_REFERENCES(names)) {
    Rf_errorcall(R_NilValue, "Internal error: `names` must not be referenced.");
  }

  R_len_t n = Rf_length(names);

  if (n == 0) {
    return;
  }

  SEXP* p_names = STRING_PTR(names);

  const int* p_locations = INTEGER_RO(locations);

  SEXP chr_empty = PROTECT(Rf_mkChar(""));

  for (R_len_t i = 0; i < n; ++i) {
    if (p_locations[i] == NA_INTEGER) {
      p_names[i] = chr_empty;
    }
  }

  UNPROTECT(1);
}
