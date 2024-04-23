

cc_library(
  name = "cp1",
  hdrs = ["cp1.h"],
  srcs = ["cp1.cc"],
)

cc_test(
  name = "cp1_test",
  size = "small",
  srcs = ["cp1_test.cc"],
  data = [
    "//testdata:test_images",
    "//testdata:test_results",
  ],
  deps = [
    ":cp1",
    "//helpers:png_utils",
    "@googletest//:gtest_main"
  ],
)

cc_test(
  name = "cp1_benchmark",
  size = "large",
  srcs = ["cp1_benchmark.cc"],
  deps = [
    ":cp1",
    "@google_benchmark//:benchmark_main",
  ]
)
