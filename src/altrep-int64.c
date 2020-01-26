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

  return R_new_altrep(altrep_int64_class_t, x, R_NilValue);
};

// {{ include("altrep-int64-api.h") }}
SEXP altrep_int64_alloc(R_xlen_t n) {
  SEXP out = PROTECT(Rf_allocVector(RAWSXP, sizeof(long long) * n));

  out = new_altrep_int64(out);

  UNPROTECT(1);
  return out;
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

// [[ init() ]]
void init_altrep_int64(DllInfo* dll) {
  altrep_int64_class_t = R_make_altraw_class("int64_int64", "int64", dll);

  // altrep
  R_set_altrep_Length_method(altrep_int64_class_t, altrep_int64_Length);
  R_set_altrep_Inspect_method(altrep_int64_class_t, altrep_int64_Inspect);

  // altvec
  R_set_altvec_Dataptr_method(altrep_int64_class_t, altrep_int64_Dataptr);
  R_set_altvec_Dataptr_or_null_method(altrep_int64_class_t, altrep_int64_Dataptr_or_null);
  //R_set_altvec_Extract_subset_method(altrep_int64_class_t, altrep_int64_Extract_subset);

  // altraw
  //R_set_altraw_Elt_method(altrep_int64_class_t, altrep_int64_Elt);
}
