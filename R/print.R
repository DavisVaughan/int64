#' @export
format.int64 <- function(x, ...) {
  format_int64(x)
}

format_int64 <- function(x) {
  .Call(export_format_int64, x)
}
