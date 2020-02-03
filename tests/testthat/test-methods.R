# ------------------------------------------------------------------------------
# is.na()

test_that("can locate NA values", {
  x <- as_int64(c(NA, 1))
  expect_equal(is.na(x), c(TRUE, FALSE))
})

# ------------------------------------------------------------------------------
# vec_order()

test_that("order is correct", {
  x <- as_int64(c(-10, 0, -5, 1, -2, 3))
  expect_equal(vec_order(x), c(1, 3, 5, 2, 4, 6))
})
