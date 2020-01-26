test_that("length is raw length divided by 8", {
  expect_equal(length(new_int64()), 0)
  expect_equal(length(new_int64(raw(8))), 1)
  expect_equal(length(new_int64(raw(16))), 2)
})

test_that("retains altrep nature on duplication", {
  x <- new_int64(raw(8))

  x_dup1 <- duplicate(x, shallow = TRUE)
  x_dup2 <- duplicate(x, shallow = FALSE)

  expect_true(is_altrep_int64(x_dup1))
  expect_true(is_altrep_int64(x_dup2))

  expect_identical(x, x_dup1)
  expect_identical(x, x_dup2)
})
