// File generated automatically by cbuild - please do not modify by hand

#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <stdbool.h> // for bool
#include <R_ext/Rdynload.h>

// .Call declarations
extern SEXP export_new_altrep_int64(SEXP);
extern SEXP export_is_altrep_int64(SEXP);
extern SEXP export_int64_as_to(SEXP, SEXP);
extern SEXP export_x_as_altrep_int64(SEXP);
extern SEXP export_int64_init_library(SEXP);
extern SEXP export_int64_is_na(SEXP);
extern SEXP export_format_int64(SEXP);
extern SEXP export_int64_slice_assign(SEXP, SEXP, SEXP);
extern SEXP export_int64_subset(SEXP, SEXP);

// .Call entries
static const R_CallMethodDef CallEntries[] = {
  {"export_new_altrep_int64",   (DL_FUNC) &export_new_altrep_int64, 1},
  {"export_is_altrep_int64",    (DL_FUNC) &export_is_altrep_int64, 1},
  {"export_int64_as_to",        (DL_FUNC) &export_int64_as_to, 2},
  {"export_x_as_altrep_int64",  (DL_FUNC) &export_x_as_altrep_int64, 1},
  {"export_int64_init_library", (DL_FUNC) &export_int64_init_library, 1},
  {"export_int64_is_na",        (DL_FUNC) &export_int64_is_na, 1},
  {"export_format_int64",       (DL_FUNC) &export_format_int64, 1},
  {"export_int64_slice_assign", (DL_FUNC) &export_int64_slice_assign, 3},
  {"export_int64_subset",       (DL_FUNC) &export_int64_subset, 2},
  {NULL, NULL, 0}
};

// Init hook declarations
void init_altrep_int64(DllInfo* dll);

void R_init_int64(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);

  init_altrep_int64(dll);
}

