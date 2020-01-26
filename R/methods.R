#' @export
is.na.int64 <- function(x) {
  .Call(export_int64_is_na, x)
}
