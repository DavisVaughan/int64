#include "utils.h"

SEXP int64_ns_env = NULL;

// {{ include("utils.h") }}
SEXP r_quote(SEXP x) {
  return Rf_lang2(Rf_install("quote"), x);
}

// {{ include("utils.h") }}
SEXP r_maybe_duplicate(SEXP x) {
  if (MAYBE_REFERENCED(x)) {
    return Rf_shallow_duplicate(x);
  } else {
    return x;
  }
}


// {{ include("utils.h") }}
SEXP int64_vec_as_location(SEXP x, R_xlen_t n, SEXP names) {
  SEXP call = PROTECT(Rf_lang4(
    Rf_install("int64_vec_as_location"),
    PROTECT(r_quote(x)),
    PROTECT(Rf_ScalarReal(n)),
    PROTECT(r_quote(names))
  ));

  SEXP out = Rf_eval(call, int64_ns_env);

  UNPROTECT(4);
  return out;
}

// {{ include("utils.h") }}
SEXP int64_vec_cast(SEXP x, SEXP to) {
  SEXP call = PROTECT(Rf_lang3(
    Rf_install("int64_vec_cast"),
    PROTECT(r_quote(x)),
    PROTECT(r_quote(to))
  ));

  SEXP out = Rf_eval(call, int64_ns_env);

  UNPROTECT(3);
  return out;
}

// {{ include("utils.h") }}
SEXP int64_vec_ptype2(SEXP x, SEXP y) {
  SEXP call = PROTECT(Rf_lang3(
    Rf_install("int64_vec_ptype2"),
    PROTECT(r_quote(x)),
    PROTECT(r_quote(y))
  ));

  SEXP out = Rf_eval(call, int64_ns_env);

  UNPROTECT(3);
  return out;
}

// {{ include("utils.h") }}
SEXP int64_vec_recycle(SEXP x, R_xlen_t size) {
  SEXP call = PROTECT(Rf_lang3(
    Rf_install("int64_vec_recycle"),
    PROTECT(r_quote(x)),
    PROTECT(Rf_ScalarReal(size))
  ));

  SEXP out = Rf_eval(call, int64_ns_env);

  UNPROTECT(3);
  return out;
}

// {{ include("utils.h") }}
SEXP int64_vec_slice(SEXP x, SEXP i) {
  SEXP call = PROTECT(Rf_lang3(
    Rf_install("int64_vec_slice"),
    PROTECT(r_quote(x)),
    PROTECT(r_quote(i))
  ));

  SEXP out = Rf_eval(call, int64_ns_env);

  UNPROTECT(3);
  return out;
}

// {{ include("init64.h") }}
void int64_init_utils(SEXP ns) {
  int64_ns_env = ns;
}
