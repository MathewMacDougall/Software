load("@rules_python//python:defs.bzl", "py_binary")
load("@dynamic_parameter_deps//:requirements.bzl", "requirement")

py_binary(
    name = "dynamic_param_v2_test",
    srcs = [":main.py"],
    data = [
        "//software/parameter_v2:parameter_configs",
    ],
    main = "main.py",
    deps = [
        requirement("PyYAML"),
    ],
)
