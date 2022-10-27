# TODO: Handle dimensionality

#' @export
vec_cast.int64_int64.int64_int64 <- function(x, to, ...) {
  x
}

#' @export
vec_cast.integer.int64_int64 <- function(x, to, ...) {
  with_oob_int64_to_int_handlers(
    .Call(ffi_cast_int64_to_int, x),
    x = x,
    to = to,
    ...,
    type = "cast"
  )
}

signal_oob_int64_to_int <- function(i) {
  signal(i = i, class = "int64:::signal_oob_int64_to_int")
}
warn_oob_int64_to_int <- function(i, x, to, ...) {
  value <- as.character(x[[i]])
  message <- cli::format_inline("Value {value} at location {i} (and possibly more locations) will be converted to `NA`.")
  warn(message)
}
stop_oob_int64_to_int <- function(i, x, to, ...) {
  value <- as.character(x[[i]])
  details <- cli::format_inline("Value {value} at location {i} would lose precision.")
  stop_incompatible_cast(x, to, ..., details = details)
}
with_oob_int64_to_int_handlers <- function(expr, x, to, ..., type) {
  try_fetch(
    expr,
    "int64:::signal_oob_int64_to_int" = function(cnd) {
      i <- cnd$i

      switch(
        type,
        cast = stop_oob_int64_to_int(i, x, to, ...),
        coerce = warn_oob_int64_to_int(i, x, to, ...),
        abort("Unknown `type`.", .internal = TRUE)
      )

      zap()
    }
  )
}

#' @export
vec_cast.int64_int64.integer <- function(x, to, ...) {
  .Call(ffi_cast_int_to_int64, x)
}

#' @export
vec_cast.double.int64_int64 <- function(x, to, ...) {
  .Call(ffi_cast_int64_to_dbl, x)
}
#' @export
vec_cast.int64_int64.double <- function(x, to, ...) {
  .Call(ffi_cast_dbl_to_int64, x)
}
