licenses(["notice"])  # BSD

package(default_visibility = ["//visibility:public"])

load("//bzl:genmsg.bzl", "gencpp_library")

#cc_library(
#    name = "std_msgs_builtin",
#    srcs = [],
#    hdrs = [
#        "include/std_msgs/builtin_bool.h",
#        "include/std_msgs/builtin_double.h",
#        "include/std_msgs/builtin_float.h",
#        "include/std_msgs/builtin_int16.h",
#        "include/std_msgs/builtin_int32.h",
#        "include/std_msgs/builtin_int64.h",
#        "include/std_msgs/builtin_int8.h",
#        "include/std_msgs/builtin_string.h",
#        "include/std_msgs/builtin_uint16.h",
#        "include/std_msgs/builtin_uint32.h",
#        "include/std_msgs/builtin_uint64.h",
#        "include/std_msgs/builtin_uint8.h",
#        "include/std_msgs/header_deprecated_def.h",
#        "include/std_msgs/trait_macros.h",
#    ],
#    strip_include_prefix = "//third_party/std_msgs/include",
#    visibility = ["//visibility:public"],
#    deps = [
#    ],
#)

cc_library(
    name = "std_msg_deps",
    deps = [
        "//third_party/cpp_common",
        "//third_party/roscpp_serialization",
        "//third_party/roscpp_traits",
    ],
)

gencpp_library(
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

gencpp_library(
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

gencpp_library(
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
