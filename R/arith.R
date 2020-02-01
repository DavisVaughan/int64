# ------------------------------------------------------------------------------
# vec_arith

#' @export
#' @rdname vctrs-compat
#' @method vec_arith int64
#' @export vec_arith.int64
vec_arith.int64 <- function(op, x, y, ...) UseMethod("vec_arith.int64", y)

#' @method vec_arith.int64 default
#' @export
vec_arith.int64.default <- function(op, x, y, ...) {
  stop_incompatible_op(op, x, y)
}

# ------------------------------------------------------------------------------

#' @method vec_arith.int64 int64
#' @export
vec_arith.int64.int64 <- function(op, x, y, ...) {
  arith_int64_int64(op, x, y)
}

arith_int64_int64 <- function(op, x, y) {
  args <- vec_recycle_common(x, y)
  x <- args[[1]]
  y <- args[[2]]

  switch(
    op,
    `+` = int64_int64_plus(x, y),
    stop_incompatible_op(op, x, y)
  )
}

int64_int64_plus <- function(x, y) {
  .Call(export_int64_int64_plus, x, y)
}


