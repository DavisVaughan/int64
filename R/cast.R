# TODO - Consider shaped inputs

#' vctrs compatibility functions
#'
#' These functions are the extensions that allow rray objects to
#' work with vctrs.
#'
#' @param x,y Objects.
#' @param to Type to cast to.
#' @param op An arithmetic operator as a string.
#' @param ... Used to pass along error message information.
#'
#' @return
#'
#' See the corresponding vctrs function for the exact return value.
#'
#' @name vctrs-compat
#'
NULL

# ------------------------------------------------------------------------------
# vec_cast

#' @export
#' @rdname vctrs-compat
#' @method vec_cast int64
#' @export vec_cast.int64
vec_cast.int64 <- function(x, to, ...) UseMethod("vec_cast.int64")

#' @method vec_cast.int64 default
#' @export
vec_cast.int64.default <- function(x, to, ..., x_arg = "x", to_arg = "to") {
  stop_incompatible_cast(x, to, x_arg = x_arg, to_arg = to_arg)
}

# ------------------------------------------------------------------------------

#' @method vec_cast.int64 int64
#' @export
vec_cast.int64.int64 <- function(x, to, ...) {
  x
}

# ------------------------------------------------------------------------------

#' @method vec_cast.int64 double
#' @export
vec_cast.int64.double <- function(x, to, ...) {
  out <- x_as_altrep_int64(x)
  new_int64(out)
}

#' @method vec_cast.double int64
#' @export
vec_cast.double.int64 <- function(x, to, ...) {
  int64_as_to(x, to)
}

# ------------------------------------------------------------------------------

#' @method vec_cast.int64 integer
#' @export
vec_cast.int64.integer <- function(x, to, ...) {
  out <- x_as_altrep_int64(x)
  new_int64(out)
}

#' @method vec_cast.integer int64
#' @export
vec_cast.integer.int64 <- function(x, to, ...) {
  int64_as_to(x, to)
}

# ------------------------------------------------------------------------------

#' @method vec_cast.int64 character
#' @export
vec_cast.int64.character <- function(x, to, ...) {
  out <- x_as_altrep_int64(x)
  new_int64(out)
}

#' @method vec_cast.character int64
#' @export
vec_cast.character.int64 <- function(x, to, ...) {
  #int64_as_to(x, to)
  abort("not yet supported")
}

# ------------------------------------------------------------------------------

int64_as_to <- function(x, to) {
  .Call(export_int64_as_to, x, to)
}

x_as_altrep_int64 <- function(x) {
  .Call(export_x_as_altrep_int64, x)
}
