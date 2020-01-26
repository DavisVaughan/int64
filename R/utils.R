class_collapse <- function(x) {
  paste0(class(x), collapse = "/")
}

glue_abort <- function(..., .sep = "", .envir = parent.frame()) {
  abort(glue(..., .sep = .sep, .envir = .envir))
}
