#' @export
as.double.int64 <- function(x) {
  vec_cast(x, double())
}

#' @export
as.integer.int64 <- function(x) {
  vec_cast(x, integer())
}
