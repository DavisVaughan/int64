# ------------------------------------------------------------------------------
# unpacking

test_that("can do the simplest unpack", {
  x <- as_int64(0L)
  x <- int64_unpack(x)

  expect_equal(
    x,
    data.frame(last = 0, first = 0)
  )
})

test_that("unpack around 0 is correct", {
  x <- as_int64(c(-1, 0, 1))
  x <- int64_unpack(x)

  last <- c(-1, 0, 0)
  first <- c(4294967295, 0, 1)

  expect_equal(
    x,
    data.frame(last = last, first = first)
  )
})

test_that("unpack around max int is correct", {
  x <- as_int64(c(.Machine$integer.max, .Machine$integer.max + 1))
  x <- int64_unpack(x)

  last <- c(0, 0)
  first <- c(.Machine$integer.max, .Machine$integer.max + 1)

  expect_equal(
    x,
    data.frame(last = last, first = first)
  )
})

test_that("flips over max unsigned int", {
  max_uint <- max_unsigned_int()

  x <- as_int64(c(max_uint, max_uint + 1))
  x <- int64_unpack(x)

  last <- c(0, 1)
  first <- c(max_uint, 0)

  expect_equal(
    x,
    data.frame(last = last, first = first)
  )
})

test_that("flips over negative max unsigned int", {
  max_uint <- max_unsigned_int()

  x <- as_int64(c(-max_uint - 2, -max_uint - 1, -max_uint))
  x <- int64_unpack(x)

  last <- c(-2, -1, -1)
  first <- c(max_uint, 0, 1)

  expect_equal(
    x,
    data.frame(last = last, first = first)
  )
})

test_that("can handle NA_integer_ as a double", {
  x <- .Machine$integer.max * -1 - 1

  x <- as_int64(x)
  x <- int64_unpack(x)

  last <- -1
  first <- 2147483648

  expect_equal(
    x,
    data.frame(last = last, first = first)
  )
})

test_that("can handle max int64", {
  x <- max_int64()
  x <- int64_unpack(x)

  last <- .Machine$integer.max
  first <- max_unsigned_int()

  expect_equal(
    x,
    data.frame(last = last, first = first)
  )
})

test_that("can handle min int64", {
  x <- min_int64()
  x <- int64_unpack(x)

  last <- .Machine$integer.max * -1 - 1
  first <- 1

  expect_equal(
    x,
    data.frame(last = last, first = first)
  )
})

# ------------------------------------------------------------------------------
# packing

test_that("can roundtrip 0", {
  x <- as_int64(0)
  expect_identical(x, int64_pack(int64_unpack(x)))
})

test_that("can roundtrip max int64", {
  x <- max_int64()
  expect_identical(x, int64_pack(int64_unpack(x)))
})

test_that("can roundtrip min int64", {
  x <- min_int64()
  expect_identical(x, int64_pack(int64_unpack(x)))
})

test_that("can roundtrip around unsigned int max", {
  x <- as_int64(max_unsigned_int() + -1:1)
  expect_identical(x, int64_pack(int64_unpack(x)))
})

test_that("can roundtrip NA", {
  x <- as_int64(NA_real_)
  expect_identical(x, int64_pack(int64_unpack(x)))
})
