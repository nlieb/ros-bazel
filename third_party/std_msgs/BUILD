licenses(["notice"])  # BSD

package(default_visibility = ["//visibility:public"])

load("//bazel:genmsg.bzl", "cc_rosmsg_library", "rosmsg_library")

cc_library(
    name = "std_msgs_builtin",
    srcs = [],
    hdrs = [
        "builtin_bool.h",
        "builtin_double.h",
        "builtin_float.h",
        "builtin_int16.h",
        "builtin_int32.h",
        "builtin_int64.h",
        "builtin_int8.h",
        "builtin_string.h",
        "builtin_uint16.h",
        "builtin_uint32.h",
        "builtin_uint64.h",
        "builtin_uint8.h",
        "header_deprecated_def.h",
        "trait_macros.h",
    ],
    strip_include_prefix = "//third_party/std_msgs/include",
    visibility = ["//visibility:public"],
    deps = [
    ],
)

rosmsg_library(
    name = "bool",
    srcs = ["msg/Bool.msg"],
)

cc_rosmsg_library(
    name = "Bool",
    src = "msg/Bool.msg",
    pkg = "std_msgs",
    #deps = [""],
)

cc_library(
    name = "std_msgs_bool",
    hdrs = ["Bool"],
)
