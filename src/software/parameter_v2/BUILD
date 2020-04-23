filegroup(
    name = "parameter_configs",
    srcs = glob([
        "config/**/*.yaml",
    ]),
    visibility = ["//software/parameter_v2:__subpackages__"],
)

cc_binary(
    name = "main",
    srcs = ["testme.cpp"],
    visibility = ["//visibility:public"],
    deps = [
        "//software/util/make_enum_macro",
    ],
)

cc_library(
    name = "test_enum",
    srcs = [],
    hdrs = [":test_enum.h"],
    deps = [],
)

exports_files(["test_enum.h"])

load(":foo.bzl", "foo_binary")

foo_binary(
    name = "bin",
    enum_srcs = [
        ":test_enum.h",
    ],
)
