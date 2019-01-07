licenses(["notice"])  # BSD

cc_library(
    name = "roscpp_serialization",
    srcs = [
        "src/serialization.cpp",
    ],
    hdrs = [
        "include/ros/roscpp_serialization_macros.h",
        "include/ros/serialization.h",
        "include/ros/serialized_message.h",
    ],
    strip_include_prefix = "//third_party/roscpp_serialization/include",
    visibility = ["//visibility:public"],
    deps = [
        "//third_party/cpp_common",
        "//third_party/roscpp_traits",
        "//third_party/rostime",
        "@boost//:call_traits",
    ],
)
