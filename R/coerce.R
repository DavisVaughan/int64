# ------------------------------------------------------------------------------

#' @export
as.character.int64_int64 <- function(x, ...) {
  .Call(ffi_coerce_int64_to_chr, x)
}
