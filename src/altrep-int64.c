#include "altrep-int64-util.h"
#include "altrep-int64-api.h"

// --------------------------------------------------------------

/*
 * Construct a new int64 altrep object.
 *
 * `data1` is used to hold the RAWSXP. It is never materialized. The use of
 * ALTREP here is mainly for the redirection in `Rf_length()`, making it so
 * that we can return a length of `length(data1) / 8`, which is the actual
 * number of int64 elements that are held in the RAWSXP object.
 *
 * @param x A RAWSXP containing a `long long` array of int64 values.
 *
 * @return A altrep int64 object where `x` is stored in `data1`, with
 *   nothing in `data2`.
 */

// {{ include("altrep-int64-api.h") }}
SEXP new_altrep_int64(SEXP x) {
  if (TYPEOF(x) != RAWSXP) {
    Rf_errorcall(
      R_NilValue,
      "Internal error: only raw SEXPs "
      "can be used to construct an altrep int64."
    );
  }

  SEXP out = R_new_altrep(altrep_int64_class_t, x, R_NilValue);

  // Copying vroom - force duplicate on modify
  MARK_NOT_MUTABLE(out);

  return out;
};

// [[ export() ]]
SEXP export_new_altrep_int64(SEXP x) {
  return new_altrep_int64(x);
}

/*
 * Allocate a new ALTREP int64 of size `n`
 *
 * @param n The size of the int64 to allocate
 *
 * @return An ALTREP int64 of size `n`
 */

// {{ include("altrep-int64-api.h") }}
SEXP altrep_int64_alloc(R_xlen_t n) {
  SEXP out = PROTECT(Rf_allocVector(RAWSXP, sizeof(long long) * n));

  out = new_altrep_int64(out);

  UNPROTECT(1);
  return out;
}

// {{ include("altrep-int64-api.h") }}
bool is_altrep_int64(SEXP x) {
  if (!ALTREP(x)) {
    return false;
  }

  if (TYPEOF(x) != RAWSXP) {
    return false;
  }

  return R_altrep_inherits(x, altrep_int64_class_t);
}

// [[ export() ]]
SEXP export_is_altrep_int64(SEXP x) {
  return Rf_ScalarLogical(is_altrep_int64(x));
}

// --------------------------------------------------------------

static R_xlen_t altrep_int64_Length(SEXP x) {
  SEXP data1 = R_altrep_data1(x);
  return Rf_xlength(data1) / 8;
}

// --------------------------------------------------------------

static Rboolean altrep_int64_Inspect(SEXP x,
                                     int pre,
                                     int deep,
                                     int pvec,
                                     void (*inspect_subtree)(SEXP, int, int, int)) {
  R_xlen_t size = altrep_int64_Length(x);

  // Never materialized!
  Rprintf("int64_int64 (len=%d, materialized=%s)\n", size, "F");

  return TRUE;
}

// --------------------------------------------------------------

// We always point to `data1`. We never materialize `data2`, because
// we don't actually need anything there.

// Never materialized
static const void* altrep_int64_Dataptr_or_null(SEXP x) {
  SEXP data1 = R_altrep_data1(x);
  return STDVEC_DATAPTR(data1);
}

// Never materialized
static void* altrep_int64_Dataptr(SEXP x, Rboolean writable) {
  SEXP data1 = R_altrep_data1(x);
  return STDVEC_DATAPTR(data1);
}

// --------------------------------------------------------------

// TODO is this right for altrep_int64_Duplicate()?
static SEXP r_altrep_maybe_duplicate(SEXP x, Rboolean deep) {
  if (deep) {
    return Rf_duplicate(x);
  }

  if (MAYBE_REFERENCED(x)) {
    return Rf_shallow_duplicate(x);
  } else {
    return x;
  }
}

static SEXP altrep_int64_Duplicate(SEXP x, Rboolean deep) {
  SEXP data1 = R_altrep_data1(x);
  data1 = PROTECT(r_altrep_maybe_duplicate(data1, deep));

  SEXP out = PROTECT(new_altrep_int64(data1));

  UNPROTECT(2);
  return out;
}

// --------------------------------------------------------------

// [[ init() ]]
void init_altrep_int64(DllInfo* dll) {
  altrep_int64_class_t = R_make_altraw_class("int64_int64", "int64", dll);

  // altrep
  R_set_altrep_Length_method(altrep_int64_class_t, altrep_int64_Length);
  R_set_altrep_Inspect_method(altrep_int64_class_t, altrep_int64_Inspect);
  R_set_altrep_Duplicate_method(altrep_int64_class_t, altrep_int64_Duplicate);

  // altvec
  R_set_altvec_Dataptr_method(altrep_int64_class_t, altrep_int64_Dataptr);
  R_set_altvec_Dataptr_or_null_method(altrep_int64_class_t, altrep_int64_Dataptr_or_null);
  //R_set_altvec_Extract_subset_method(altrep_int64_class_t, altrep_int64_Extract_subset);

  // altraw
  //R_set_altraw_Elt_method(altrep_int64_class_t, altrep_int64_Elt);
}
