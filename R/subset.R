#' @export
`[.int64` <- function(x, i, ...) {
  int64_subset(x, i)
}

int64_subset <- function(x, i) {
  .Call(export_int64_subset, x, i)
}
