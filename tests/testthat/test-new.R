# ------------------------------------------------------------------------------
# int64()

test_that("helper validates length", {
  expect_error(int64(raw(8)), NA)
  expect_error(int64(raw(2)), "divisible by 8, not 2")
})

# ------------------------------------------------------------------------------
# new_int64()

test_that("can construct empty int64 objects", {
  expect_is(new_int64(), c("int64", "vctrs_vctr"))
})

test_that("can construct sized int64 objects", {
  x <- c(raw(8), raw(8))
  expect_is(new_int64(x), c("int64", "vctrs_vctr"))
})

test_that("int64 objects are actually altrep int64", {
  expect_false(is_altrep_int64(raw()))
  expect_true(is_altrep_int64(new_int64()))
})
