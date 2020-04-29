filegroup(
    name = "parameter_configs",
    srcs = glob([
        "config/**/*.yaml",
    ]),
    visibility = ["//shared/parameter_v2:__subpackages__"],
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

cc_library(
    name = "test_enum_dep",
    srcs = [],
    hdrs = [":test_enum_dep.h"],
    deps = [],
)

exports_files(["test_enum.h"])

load(":parameter.bzl", "generate_dynamic_parameters")

generate_dynamic_parameters(
    name = "dynamic_params",
    enum_targets = [
        ":test_enum",
    ],
    generated_config_file = "myconfiguration.hpp",
)
