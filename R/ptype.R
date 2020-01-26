# ------------------------------------------------------------------------------
# vec_ptype2

#' @export
#' @rdname vctrs-compat
#' @method vec_ptype2 int64
#' @export vec_ptype2.int64
vec_ptype2.int64 <- function(x, y, ...) {
  UseMethod("vec_ptype2.int64", y)
}

#' @method vec_ptype2.int64 default
#' @export
vec_ptype2.int64.default <- function(x, y, ..., x_arg = "x", y_arg = "y") {
  stop_incompatible_type(x, y, x_arg = x_arg, y_arg = y_arg)
}

# ------------------------------------------------------------------------------

#' @method vec_ptype2.int64 int64
#' @export
vec_ptype2.int64.int64 <- function(x, y, ...) {
  global_empty_int64
}

# ------------------------------------------------------------------------------

# Purposefully exporting these. Common type of int64 and double is unclear,
# so it shouldn't exist. int64 can hold a larger integer number, but double
# can hold fractional values.

#' @method vec_ptype2.int64 double
#' @export
vec_ptype2.int64.double <- function(x, y, ...) {
  stop_incompatible_type(x, y, x_arg = x_arg, y_arg = y_arg)
}

#' @method vec_ptype2.double int64
#' @export
vec_ptype2.double.int64 <- function(x, y, ...) {
  stop_incompatible_type(x, y, x_arg = x_arg, y_arg = y_arg)
}

# ------------------------------------------------------------------------------

#' @method vec_ptype2.int64 integer
#' @export
vec_ptype2.int64.integer <- function(x, y, ...) {
  global_empty_int64
}

#' @method vec_ptype2.integer int64
#' @export
vec_ptype2.integer.int64 <- function(x, y, ...) {
  global_empty_int64
}
