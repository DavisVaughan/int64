
#' @export
as_int64 <- function(x) {
  UseMethod("as_int64")
}

#' @export
as_int64.default <- function(x) {
  stop_input_type(x, "coercible to int64")
}

#' @export
as_int64.integer <- function(x) {
  .Call(ffi_coerce_int_to_int64, x)
}

# ------------------------------------------------------------------------------

#' @export
as.character.int64_int64 <- function(x, ...) {
  .Call(ffi_coerce_int64_to_chr, x)
}

# ------------------------------------------------------------------------------

#' @export
as.integer.int64_int64 <- function(x, ...) {
  with_oob_int64_to_int_handlers(
    .Call(ffi_coerce_int64_to_int, x),
    x = x,
    to = to,
    ...,
    type = "coerce"
  )
}



