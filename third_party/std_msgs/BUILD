licenses(["notice"])  # BSD

package(default_visibility = ["//visibility:public"])

load("//bzl:genmsg.bzl", "cc_rosmsg_library")

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

cc_library(
    name = "std_msg_deps",
    deps = [
        "//third_party/cpp_common",
        "//third_party/roscpp_serialization",
        "//third_party/roscpp_traits",
    ],
)

cc_rosmsg_library(
    name = "cc_bool",
    src = "msg/Bool.msg",
    pkg = "std_msgs",
)

cc_library(
    name = "Bool",
    hdrs = [":cc_bool"],
    linkstatic = 1,
    strip_include_prefix = "//third_party",
    deps = [":std_msg_deps"],
)

cc_rosmsg_library(
    name = "cc_header",
    src = "msg/Header.msg",
    pkg = "std_msgs",
)

cc_library(
    name = "Header",
    hdrs = [":cc_header"],
    linkstatic = 1,
    strip_include_prefix = "//third_party",
    deps = [":std_msg_deps"],
)

# String

cc_rosmsg_library(
    name = "cc_string",
    src = "msg/String.msg",
    pkg = "std_msgs",
)

cc_library(
    name = "String",
    hdrs = [":cc_string"],
    linkstatic = 1,
    strip_include_prefix = "//third_party",
    deps = [":std_msg_deps"],
)
