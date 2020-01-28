#' @export
`[.int64` <- function(x, i, ...) {
  int64_subset(x, i)
}

#' @export
`[[.int64` <- function(x, i, ...) {
  i <- vec_as_location2(i, length(x), names = names(x))
  x <- unname(x)
  int64_subset(x, i)
}

int64_subset <- function(x, i) {
  .Call(export_int64_subset, x, i)
}
