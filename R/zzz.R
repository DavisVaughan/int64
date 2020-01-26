# nocov start

global_empty_int64 <- NULL

.onLoad <- function(libname, pkgname) {
  global_empty_int64 <<- new_int64()
}

# nocov end
