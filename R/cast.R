# TODO: Handle dimensionality

#' @export
vec_cast.int64_int64.int64_int64 <- function(x, to, ...) {
  x
}

#' @export
vec_cast.integer.int64_int64 <- function(x, to, ...) {
  .Call(ffi_cast_int64_to_integer, x)
}
#' @export
vec_cast.int64_int64.integer <- function(x, to, ...) {
  .Call(ffi_cast_int_to_int64, x)
}

#' @export
vec_cast.double.int64_int64 <- function(x, to, ...) {
  .Call(ffi_cast_int64_to_double, x)
}
#' @export
vec_cast.int64_int64.double <- function(x, to, ...) {
  .Call(ffi_cast_double_to_int64, x)
}
