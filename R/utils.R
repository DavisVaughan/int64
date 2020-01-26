class_collapse <- function(x) {
  paste0(class(x), collapse = "/")
}

glue_abort <- function(..., .sep = "", .envir = parent.frame()) {
  abort(glue(..., .sep = .sep, .envir = .envir))
}

# Called from C
int64_subscript_as_location <- function(x, n, names) {
  vec_as_location(x, n, names)
}
