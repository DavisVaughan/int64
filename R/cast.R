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
warn_oob_int64_to_int <- function(i, x, ...) {
  value <- as.character(x[[i]])

  message <- c(
    i = "Coercing <int64> to <integer> will lose precision.",
    i = "Lossy values will be converted to `NA`.",
    i = cli::format_inline("First detected at location {i} with value {value}.")
  )

  warn(message)
}
stop_oob_int64_to_int <- function(i, x, to, ...) {
  value <- as.character(x[[i]])

  details <- c(
    i = "Converting <int64> to <integer> would lose precision.",
    i = cli::format_inline("First detected at location {i} with value {value}.")
  )

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
        coerce = warn_oob_int64_to_int(i, x, ...),
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
