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
    name = "cc_set_bool",
    src = "srv/SetBool.srv",
    pkg = "std_srvs",
)

cc_library(
    name = "SetBool",
    hdrs = [":cc_set_bool"],
    strip_include_prefix = "//third_party",
    deps = [":std_msg_deps"],
)
