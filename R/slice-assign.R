#' @export
`[<-.int64` <- function(x, i, ..., value) {
  int64_slice_assign(x, i, value)
}

int64_slice_assign <- function(x, i, value) {
  .Call(export_int64_slice_assign, x, i, value)
}
