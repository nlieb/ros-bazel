licenses(["notice"])  # BSD

cc_library(
    name = "roscpp_traits",
    hdrs = [
        "include/ros/builtin_message_traits.h",
        "include/ros/message_event.h",
        "include/ros/message_forward.h",
        "include/ros/message_operations.h",
        "include/ros/message_traits.h",
        "include/ros/service_traits.h",
    ],
    strip_include_prefix = "//third_party/roscpp_traits/include",
    visibility = ["//visibility:public"],
    deps = [
        "//third_party/cpp_common",
        "//third_party/rostime",
    ],
)
