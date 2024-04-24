


cc_library(
  name = "mf1",
  hdrs = ["mf1.h"],
  srcs = ["mf1.cc"],
)

cc_test(
  name = "mf1_test",
  size = "small",
  srcs = ["mf1_test.cc"],
  data = [
    "//testdata:test_images",
    "//testdata:test_results",
  ],
  deps = [
    ":mf1",
    "//helpers:png_utils",
    "@googletest//:gtest_main"
  ],
)

cc_test(
  name = "mf1_benchmark",
  size = "large",
  srcs = ["mf1_benchmark.cc"],
  deps = [
    ":mf1",
    "@google_benchmark//:benchmark_main",
  ]
)
