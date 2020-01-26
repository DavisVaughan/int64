#' Coerce to int64
#'
#' @param x An object to coerce
#'
#' @return An int64 object with the same size as `x`.
#'
#' @export
as_int64 <- function(x) {
  vec_cast(x, global_empty_int64)
}

#' @export
as.double.int64 <- function(x) {
  vec_cast(x, double())
}

#' @export
as.integer.int64 <- function(x) {
  vec_cast(x, integer())
}
