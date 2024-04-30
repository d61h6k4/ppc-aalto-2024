

cc_library(
  name = "is2",
  hdrs = ["is.h"],
  srcs = ["is2.cc"],
)

cc_test(
  name = "is2_test",
  size = "large",
  srcs = ["is2_test.cc"],
  data = [
    "//testdata:test_images",
  ],
  deps = [
    ":is2",
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
