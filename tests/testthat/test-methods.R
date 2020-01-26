# ------------------------------------------------------------------------------
# is.na()

test_that("can locate NA values", {
  x <- as_int64(c(NA, 1))
  expect_equal(is.na(x), c(TRUE, FALSE))
})
