#include "int64.h"
#include <errno.h>
#include <ctype.h>

// -----------------------------------------------------------------------------
// Cast int64 -> to

static SEXP int64_as_double(SEXP x) {
  long long* p_x = INT64(x);

  R_xlen_t size = Rf_xlength(x);

  SEXP out = PROTECT(Rf_allocVector(REALSXP, size));
  double* p_out = REAL(out);

  for (R_xlen_t i = 0; i < size; ++i) {
    long long elt = p_x[i];

    if (elt == NA_INT64) {
      p_out[i] = NA_REAL;
      continue;
    }

    // TODO - Lossy! What value to use? Largest double where all integer values
    // below it are representable with ints?
    //if (elt < DBL_MIN || elt > DBL_MAX) {
    //  p_out[i] = NA_REAL;
    //  continue;
    //}

    p_out[i] = (double) elt;
  }

  UNPROTECT(1);
  return out;
}

static SEXP int64_as_integer(SEXP x) {
  long long* p_x = INT64(x);

  R_xlen_t size = Rf_xlength(x);

  SEXP out = PROTECT(Rf_allocVector(INTSXP, size));
  int* p_out = INTEGER(out);

  for (R_xlen_t i = 0; i < size; ++i) {
    long long elt = p_x[i];

    if (elt == NA_INT64) {
      p_out[i] = NA_INTEGER;
      continue;
    }

    // TODO - Lossy warning!
    if (elt < INT_MIN || elt > INT_MAX) {
      p_out[i] = NA_INTEGER;
      continue;
    }

    p_out[i] = (int) elt;
  }

  UNPROTECT(1);
  return out;
}

static SEXP int64_as_to(SEXP x, SEXP to) {
  switch(TYPEOF(to)) {
  case REALSXP:
    return int64_as_double(x);
  case INTSXP:
    return int64_as_integer(x);
  case LGLSXP:
  case STRSXP:
  case RAWSXP:
  default: Rf_errorcall(R_NilValue, "Cannot cast");
  }
}

// [[ export() ]]
SEXP export_int64_as_to(SEXP x, SEXP to) {
  return int64_as_to(x, to);
}

// -----------------------------------------------------------------------------
// Cast to -> altrep int64

// Anything above or below this is a double value that cannot be represented
// exactly, meaning that there is no way to know if it has a floating part or
// not, so we consider that to be lossy automatically. For example, try:
// options(digits = 22)
// 2^53 # 9007199254740992
// 2^53 + 1 # 9007199254740992 same as before!!
// 2^53 + 2 # 9007199254740994
#define MAX_CONTIGUOUSLY_REPRESENTABLE_DBL (9007199254740992)
#define MIN_CONTIGUOUSLY_REPRESENTABLE_DBL (-9007199254740992)

static SEXP dbl_as_altrep_int64(SEXP x) {
  double* p_x = REAL(x);

  R_xlen_t size = Rf_xlength(x);

  SEXP out = PROTECT(altrep_int64_alloc(size));
  long long* p_out = INT64(out);

  for (R_xlen_t i = 0; i < size; ++i) {
    double elt = p_x[i];

    if (isnan(elt)) {
      p_out[i] = NA_INT64;
      continue;
    }

    // TODO - Lossy warning!
    if (elt > MAX_CONTIGUOUSLY_REPRESENTABLE_DBL ||
        elt < MIN_CONTIGUOUSLY_REPRESENTABLE_DBL) {
      p_out[i] = NA_INT64;
      continue;
    }

    long long value = (long long) elt;

    // TODO - Lossy warning!
    if (value != elt) {
      p_out[i] = NA_INT64;
      continue;
    }

    p_out[i] = value;
  }

  UNPROTECT(1);
  return out;
}

static SEXP int_as_altrep_int64(SEXP x) {
  int* p_x = INTEGER(x);

  R_xlen_t size = Rf_xlength(x);

  SEXP out = PROTECT(altrep_int64_alloc(size));
  long long* p_out = INT64(out);

  for (R_xlen_t i = 0; i < size; ++i) {
    int elt = p_x[i];

    if (elt == NA_INTEGER) {
      p_out[i] = NA_INT64;
      continue;
    }

    p_out[i] = (long long) elt;
  }

  UNPROTECT(1);
  return out;
}

static void trim_trailing_whitespace(char* out, size_t len, const char* x) {
  // Find where trailing whitespace ends
  const char* end = x + len - 1;
  while(end > x && isspace((unsigned char) *end)) {
    --end;
  };
  ++end;

  // Set output size to minimum of trimmed string length and buffer size minus 1
  size_t out_size = (end - x) < len - 1 ? (end - x) : len - 1;

  // Copy trimmed string and add null terminator
  memcpy(out, x, out_size);
  out[out_size] = 0;

  return;
}

static long long trim_trailing_whitespace_and_retry(const char* x) {
  size_t len = strlen(x);
  char x_trimmed[len];

  trim_trailing_whitespace(x_trimmed, len, x);

  char* endpointer;

  long long x_int64 = strtoll(x_trimmed, &endpointer, 10);

  // We could have extra data that went outside the range of representable
  // long longs. Return NA
  if (errno == ERANGE) {
    errno = 0;
    return(NA_INT64);
  }

  // We trimmed, but still either couldn't parse or had extra data
  if (*endpointer) {
    return(NA_INT64);
  }

  return x_int64;
}

static SEXP str_as_altrep_int64(SEXP x) {
  SEXP* p_x = STRING_PTR(x);

  R_xlen_t size = Rf_xlength(x);

  SEXP out = PROTECT(altrep_int64_alloc(size));
  long long* p_out = INT64(out);

  // Reset errno to 0 in case something else has modified it
  errno = 0;

  for (R_xlen_t i = 0; i < size; ++i) {
    SEXP elt = p_x[i];

    if (elt == NA_STRING) {
      p_out[i] = NA_INT64;
      continue;
    }

    const char* elt_char = CHAR(elt);
    char* endpointer;

    // const char* x, char* endpointer, int base
    long long elt_int64 = strtoll(elt_char, &endpointer, 10);

    // In case we go `> LLONG_MAX` or `< LLONG_MIN`
    if (errno == ERANGE) {
      errno = 0;
      p_out[i] = NA_INT64;
      continue;
    }

    // - If there are any leftover values, trim trailing whitespace
    //   and retry. If it works after that then all good, otherwise return NA.
    // - This also captures if it couldn't convert at all, which returns
    //   a 0 into elt_int64 and sets the endpointer to the first element
    //   of the char array
    if (*endpointer) {
      p_out[i] = trim_trailing_whitespace_and_retry(elt_char);
      continue;
    }

    p_out[i] = elt_int64;
  }

  UNPROTECT(1);
  return out;
}

static SEXP x_as_altrep_int64(SEXP x) {
  switch(TYPEOF(x)) {
  case REALSXP:
    return dbl_as_altrep_int64(x);
  case INTSXP:
    return int_as_altrep_int64(x);
  case STRSXP:
    return str_as_altrep_int64(x);
  case LGLSXP:
  case RAWSXP:
  default: Rf_errorcall(R_NilValue, "Cannot cast");
  }
}

// [[ export() ]]
SEXP export_x_as_altrep_int64(SEXP x) {
  return x_as_altrep_int64(x);
}
