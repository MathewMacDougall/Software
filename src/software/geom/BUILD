package(default_visibility = ["//visibility:public"])

cc_library(
    name = "geom",
    srcs = [
        "shot.cpp",
        "util.cpp",
        "voronoi_diagram.cpp",
    ],
    hdrs = [
        "shot.h",
        "util.h",
        "voronoi_diagram.h",
    ],
    deps = [
        "//software/logger",
        "//software/new_geom:circle",
        "//software/new_geom:line",
        "//software/new_geom:point",
        "//software/new_geom:point_boost_geometry_compatability",
        "//software/new_geom:polygon",
        "//software/new_geom:ray",
        "//software/new_geom:rectangle",
        "//software/new_geom:triangle",
        "//software/new_geom/util:collinear",
        "//software/new_geom/util:distance",
        "//software/new_geom/util:intersection",
        "//software/new_geom/util:intersects",
        "@boost//:geometry",
        "@boost//:polygon",
    ],
)

cc_test(
    name = "util_test",
    srcs = [
        "util_test.cpp",
    ],
    deps = [
        ":geom",
        "//software/test_util",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "voronoi_util_test",
    srcs = [
        "voronoi_diagram_test.cpp",
    ],
    deps = [
        ":geom",
        "//software/test_util",
        "@gtest//:gtest_main",
    ],
)
