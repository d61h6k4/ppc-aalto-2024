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

cc_library(
  name = "cp2a",
  hdrs = ["cp2a.h"],
  srcs = ["cp2a.cc"],
)

cc_test(
  name = "cp2a_test",
  size = "small",
  srcs = ["cp2a_test.cc"],
  data = [
    "//testdata:test_images",
    "//testdata:test_results",
  ],
  deps = [
    ":cp2a",
    "//helpers:png_utils",
    "@googletest//:gtest_main"
  ],
)

cc_test(
  name = "cp2a_benchmark",
  size = "large",
  srcs = ["cp2a_benchmark.cc"],
  deps = [
    ":cp2a",
    "@google_benchmark//:benchmark_main",
  ]
)


cc_library(
  name = "ops",
  hdrs = ["ops.h"],
  deps = [
    "@highway//:hwy",
  ]
)


cc_test(
  name = "ops_test",
  size = "small",
  srcs = ["ops_test.cc"],
  deps = [
    ":ops",
    "@highway//:hwy_test_util",
    "@googletest//:gtest_main"
  ],
)

cc_library(
  name = "cp2",
  hdrs = ["cp2.h"],
  srcs = ["cp2.cc"],
  deps = [
    ":ops",
    "@highway//:hwy",
  ]
)


cc_test(
  name = "cp2_test",
  size = "small",
  srcs = ["cp2_test.cc"],
  data = [
    "//testdata:test_images",
    "//testdata:test_results",
  ],
  deps = [
    ":cp2",
    "@highway//:hwy_test_util",
    "//helpers:png_utils",
    "@googletest//:gtest_main"
  ],
)


cc_test(
  name = "cp2_benchmark",
  size = "large",
  srcs = ["cp2_benchmark.cc"],
  deps = [
    ":cp2",
    "@google_benchmark//:benchmark_main",
  ]
)
