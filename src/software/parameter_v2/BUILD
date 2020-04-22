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
