// File generated automatically by cbuild - please do not modify by hand

#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <stdbool.h> // for bool
#include <R_ext/Rdynload.h>

// .Call declarations
extern SEXP int64_new_altrep_int64(SEXP);
extern SEXP int64_is_altrep_int64(SEXP);
extern SEXP new_empty_int64();

// .Call entries
static const R_CallMethodDef CallEntries[] = {
  {"int64_new_altrep_int64", (DL_FUNC) &int64_new_altrep_int64, 1},
  {"int64_is_altrep_int64",  (DL_FUNC) &int64_is_altrep_int64, 1},
  {"new_empty_int64",        (DL_FUNC) &new_empty_int64, 0},
  {NULL, NULL, 0}
};

// Init hook declarations
void init_altrep_int64(DllInfo* dll);

void R_init_int64(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);

  init_altrep_int64(dll);
}

