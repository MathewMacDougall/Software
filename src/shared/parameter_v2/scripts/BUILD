load("@rules_python//python:defs.bzl", "py_binary")
load("@dynamic_parameter_deps//:requirements.bzl", "requirement")

py_binary(
    name = "dynamic_param_v2_test",
    srcs = [":main.py"],
    data = [
        "//shared/parameter_v2:parameter_configs",
    ],
    main = "main.py",
    visibility = ["//shared/parameter_v2:__subpackages__"],
    deps = [
        requirement("PyYAML"),
        "@rules_python//python/runfiles",
    ],
)

# TODO: You are here. Trying to find a good way to access data dependencies,
# bonus if it works well running under python or bazel. Try just using relative
# paths from the file/module, since it seems like the data deps show up in
# the same tree in the bazel output
