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

test_that("can slice correctly", {
  x <- as_int64(6:10)

  expect_equal(
    x[1:3],
    as_int64(as.integer(x)[1:3])
  )

  expect_equal(
    x[c(1, 1, 5)],
    as_int64(as.integer(x)[c(1, 1, 5)])
  )

  expect_equal(
    x[-1],
    as_int64(as.integer(x)[-1])
  )
})

test_that("can slice with names", {
  x <- as_int64(1:2)
  names(x) <- c("x", "y")

  expect <- as_int64(1)
  names(expect) <- "x"

  expect_equal(
    x["x"],
    expect
  )

  expect_true(is_altrep_int64(x["x"]))
})

test_that("can slice with NA_integer_", {
  x <- as_int64(1:5)

  expect_equal(
    x[c(NA_integer_, NA_integer_)],
    as_int64(as.integer(x)[c(NA_integer_, NA_integer_)])
  )
})

test_that("using vec_as_location() for subscripts", {
  x <- as_int64(1:5)

  verify_output(
    test_path("errors/test-subscript-oob.txt"),
    x[6]
  )

  verify_output(
    test_path("errors/test-subscript-oob-negate.txt"),
    x[-6]
  )

  y <- as_int64(1:2)
  names(y) <- c("x", "y")

  verify_output(
    test_path("errors/test-subscript-oob-names.txt"),
    y["z"]
  )
})
