
cc_library(
    name = "image",
    hdrs = ["image.h"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "png_utils",
    hdrs = ["png_utils.h"],
    srcs = ["png_utils.cc"],
    visibility = ["//visibility:public"],
    deps = [
        ":image",
        "@libpng//:png",
    ]
)

cc_library(
    name = "bmp_utils",
    hdrs = ["bmp_utils.h"],
    srcs = ["bmp_utils.cc"],
    visibility = ["//visibility:public"],
    deps = [
        ":image"
    ]
)

cc_test(
    name = "png_utils_test",
    srcs = ["png_utils_test.cc"],
    data = [
        "//testdata:test_images",
    ],
    deps = [
        ":png_utils",
        "@googletest//:gtest_main"
    ]
)

cc_test(
    name = "bmp_utils_test",
    srcs = ["bmp_utils_test.cc"],
    data = [
        "//testdata:test_images",
    ],
    deps = [
        ":bmp_utils",
        ":png_utils",
        "@googletest//:gtest_main"
    ]
)
