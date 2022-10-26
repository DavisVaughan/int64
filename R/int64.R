int64 <- function(...) {
  args <- list2(...)
  names(args) <- NULL

  args <- vec_cast_common(!!!args, .to = new_int64())

  list_unchop(args, ptype = new_int64())
}

new_int64 <- function(x = complex()) {
  if (!is_complex(x)) {
    stop_input_type(x, "complex")
  }

  new_vctr(
    x,
    class = "int64_int64",
    inherit_base_type = FALSE
  )
}

#' @export
is_int64 <- function(x) {
  inherits(x, "int64_int64")
}

# ------------------------------------------------------------------------------

#' @export
format.int64_int64 <- function(x, ...) {
  out <- as.character(x)

  if (vec_any_missing(out)) {
    # Follow `format()` for numeric types, which encodes with quoted `"NA"`
    missing <- vec_detect_missing(out)
    out[missing] <- "NA"
  }

  out
}

# ------------------------------------------------------------------------------

#' @export
vec_ptype_full.int64_int64 <- function(x, ...) {
  "int64"
}

#' @export
vec_ptype_abbr.int64_int64 <- function(x, ...) {
  "int64"
}

# ------------------------------------------------------------------------------

#' @export
vec_ptype2.int64_int64.int64_int64 <- function(x, y, ...) {
  x
}

#' @export
vec_ptype2.int64_int64.integer <- function(x, y, ...) {
  x
}
#' @export
vec_ptype2.integer.int64_int64 <- function(x, y, ...) {
  y
}

