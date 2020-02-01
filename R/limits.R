max_unsigned_int <- function() {
  .Call(export_max_unsigned_int)
}

max_int64 <- function() {
  .Call(export_max_int64)
}

min_int64 <- function() {
  .Call(export_min_int64)
}
