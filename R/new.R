# Might not be the most useful constructor, assumes raw input
int64 <- function(x) {
  if (length(x) %% 8L != 0L) {
    glue_abort("`x` must have a size divisible by 8, not {length(x)}.")
  }

  new_int64(x)
}

# ------------------------------------------------------------------------------

new_int64 <- function(x = raw(), ..., class = character()) {
  if (!is.raw(x)) {
    glue_abort("`x` must have type raw, not {class_collapse(x)}.")
  }

  if (!is_altrep_int64(x)) {
    x <- new_altrep_int64(x)
  }

  new_int64_vctr(x, ..., class = class)
}

# ------------------------------------------------------------------------------

new_int64_vctr <- function(x, ..., class) {
  new_vctr(x, ..., class = c(class, "int64"), inherit_base_type = FALSE)
}

# ------------------------------------------------------------------------------

new_altrep_int64 <- function(x) {
  .Call(int64_new_altrep_int64, x)
}

is_altrep_int64 <- function(x) {
  .Call(int64_is_altrep_int64, x)
}
