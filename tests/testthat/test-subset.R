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

test_that("can slice with `vec_slice()`, going through `Extract_subset()`", {
  x <- as_int64(1:5)
  names(x) <- letters[1:5]

  expect_equal(names(vec_slice(x, c(1, 3))), c("a", "c"))

  expect_equal(vec_slice(x, 1), x[1])
  expect_equal(vec_slice(x, c(1, 5)), x[c(1, 5)])
})

test_that("NA names are repaired to the empty string", {
  x <- as_int64(1:2)
  names(x) <- c("x", "y")

  expect_named(x[NA_integer_], "")
  expect_named(x[c(1, NA_integer_)], c("x", ""))

  expect_named(vec_slice(x, NA_integer_), "")
  expect_named(vec_slice(x, c(1, NA_integer_)), c("x", ""))
})

test_that("can use `[[` to extract elements", {
  x <- as_int64(1:2)
  expect_identical(x[[1]], as_int64(1))
})

test_that("`[[` drops names", {
  x <- as_int64(1:2)
  names(x) <- c("x", "y")
  expect_named(x[[1]], NULL)
})

test_that("`[[` uses vec_as_location2() errors", {
  x <- as_int64(1:5)

  verify_output(
    test_path("errors/test-subscript2-oob.txt"),
    x[[6]]
  )

  verify_output(
    test_path("errors/test-subscript2-oob-negate.txt"),
    x[[-1]]
  )

  y <- as_int64(1:2)
  names(y) <- c("x", "y")

  verify_output(
    test_path("errors/test-subscript2-oob-names.txt"),
    y[["z"]]
  )
})
