package(default_visibility = ["//visibility:public"])

cc_library(
    name = "ai",
    srcs = ["ai.cpp"],
    hdrs = ["ai.h"],
    # We include all the plays here so that the static
    # variables in the .cpp files that auto-register plays with the
    # PlayFactory. This addresses the issue explained here:
    # https://www.bfilipek.com/2018/02/static-vars-static-lib.html
    deps = [
        "//software/ai/hl/stp",
        "//software/ai/hl/stp:play_info",
        "//software/ai/hl/stp/play:all_plays",
        "//software/ai/hl/stp/play:halt_play",
        "//software/ai/navigator",
        "//software/ai/navigator/path_manager:velocity_obstacle_path_manager",
        "//software/ai/navigator/path_planner:theta_star_path_planner",
        "//software/primitive",
        "//software/time:timestamp",
        "//software/world",
    ],
)

cc_library(
    name = "ai_wrapper",
    srcs = ["ai_wrapper.cpp"],
    hdrs = ["ai_wrapper.h"],
    deps = [
        "//software/ai",
        "//software/gui/visualizer/drawing:draw_functions",
        "//software/gui/visualizer/drawing:navigator",
        "//software/multithreading:subject",
        "//software/multithreading:threaded_observer",
        "//software/parameter:dynamic_parameters",
        "//software/world",
        "@boost//:bind",
    ],
)
