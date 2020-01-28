class_collapse <- function(x) {
  paste0(class(x), collapse = "/")
}

glue_abort <- function(..., .sep = "", .envir = parent.frame()) {
  abort(glue(..., .sep = .sep, .envir = .envir))
}

# Called from C
int64_vec_as_location <- function(x, n, names) {
  vec_as_location(x, n, names)
}

# Called from C
int64_vec_cast <- function(x, to) {
  vec_cast(x, to)
}

# Called from C
int64_vec_ptype2 <- function(x, y) {
  vec_ptype2(x, y)
}

# Called from C
int64_vec_recycle <- function(x, size) {
  vec_recycle(x, size)
}

# Called from C
int64_vec_slice <- function(x, i) {
  vec_slice(x, i)
}
