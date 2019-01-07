licenses(["notice"])  # BSD

cc_library(
    name = "rostime",
    srcs = [
        "src/duration.cpp",
        "src/rate.cpp",
        "src/time.cpp",
    ],
    hdrs = [
        "include/ros/duration.h",
        "include/ros/impl/duration.h",
        "include/ros/impl/time.h",
        "include/ros/rate.h",
        "include/ros/rostime_decl.h",
        "include/ros/time.h",
    ],
    strip_include_prefix = "//third_party/rostime/include",
    visibility = ["//visibility:public"],
    deps = [
        "//third_party/cpp_common",
        "@boost//:date_time",
        "@boost//:thread",
    ],
)
