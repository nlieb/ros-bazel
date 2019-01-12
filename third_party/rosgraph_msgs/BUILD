licenses(["notice"])  # BSD

package(default_visibility = ["//visibility:public"])

load("//bzl:genmsg.bzl", "gencpp_library")

cc_library(
    name = "std_msg_deps",
    deps = [
        "//third_party/cpp_common",
        "//third_party/roscpp_serialization",
        "//third_party/roscpp_traits",
    ],
)

gencpp_library(
    name = "cc_log",
    src = "msg/Log.msg",
    pkg = "rosgraph_msgs",
    deps = ["//third_party/std_msgs:cc_header"],
)

cc_library(
    name = "Log",
    hdrs = [":cc_log"],
    linkstatic = 1,
    strip_include_prefix = "//third_party",
    deps = [
        ":std_msg_deps",
    ],
)

gencpp_library(
    name = "cc_topic_statistics",
    src = "msg/TopicStatistics.msg",
    pkg = "rosgraph_msgs",
    deps = [],
)

cc_library(
    name = "TopicStatistics",
    hdrs = [":cc_topic_statistics"],
    linkstatic = 1,
    strip_include_prefix = "//third_party",
    deps = [
        ":std_msg_deps",
    ],
)

gencpp_library(
    name = "cc_clock",
    src = "msg/Clock.msg",
    pkg = "rosgraph_msgs",
    deps = [],
)

cc_library(
    name = "Clock",
    hdrs = [":cc_clock"],
    linkstatic = 1,
    strip_include_prefix = "//third_party",
    deps = [
        ":std_msg_deps",
    ],
)
