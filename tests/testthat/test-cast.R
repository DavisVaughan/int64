# ------------------------------------------------------------------------------
# character -> int64

test_that("can convert character to int64", {
  expect_equal(vec_cast("1", new_int64()), as_int64(1))
  expect_equal(vec_cast("0", new_int64()), as_int64(0))
  expect_equal(vec_cast("-1", new_int64()), as_int64(-1))
})

test_that("can convert max and min long long values", {
  expect_false(is.na(vec_cast("9223372036854775807", new_int64())))
  expect_false(is.na(vec_cast("-9223372036854775807", new_int64())))
})

test_that("above max long long and below min long long are NA", {
  expect_true(is.na(vec_cast("9223372036854775808", new_int64())))
  expect_true(is.na(vec_cast("-9223372036854775808", new_int64())))
})

test_that("non numeric-like strings are converted to NA", {
  expect_true(is.na(vec_cast("stuff", new_int64())))
})

test_that("numeric-like strings with trailing blanks can be converted", {
  expect_equal(vec_cast("1 ", new_int64()), as_int64(1))
  expect_equal(vec_cast("1 x", new_int64()), as_int64(NA_integer_))
})

test_that("numeric-like strings with leading blanks can be converted", {
  expect_equal(vec_cast("1 ", new_int64()), as_int64(1))
  expect_equal(vec_cast("x 1 ", new_int64()), as_int64(NA_integer_))
})

test_that("above max long long is still NA if there are spaces", {
  expect_true(is.na(vec_cast(" 9223372036854775808", new_int64())))
  expect_true(is.na(vec_cast("9223372036854775808 ", new_int64())))
})
