# nocov start

global_empty_int64 <- NULL

.onLoad <- function(libname, pkgname) {
  global_empty_int64 <<- new_int64()

  .Call(export_int64_init_library, asNamespace("int64"))
}

# nocov end
