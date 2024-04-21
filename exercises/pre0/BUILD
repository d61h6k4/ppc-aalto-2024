
cc_library(
  name = "pre0",
  hdrs = ["pre0.h"],
  srcs = ["pre0.cc"],
)

cc_test(
  name = "pre0_test",
  size = "small",
  srcs = ["pre0_test.cc"],
  deps = [
    ":pre0",
    "@googletest//:gtest_main"
  ],
)

cc_test(
  name = "pre0_benchmark",
  size = "small",
  srcs = ["pre0_benchmark.cc"],
  deps = [
    "pre0",
    "@google_benchmark//:benchmark_main",
  ]
)
