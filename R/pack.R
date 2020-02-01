int64_pack <- function(x) {
  .Call(export_int64_pack, x)
}

int64_unpack <- function(x) {
  .Call(export_int64_unpack, x)
}
