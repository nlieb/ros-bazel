licenses(["notice"])  # BSD

cc_library(
    name = "rosconsole_glog",
    srcs = [
        "src/rosconsole/impl/rosconsole_glog.cpp",
    ],
    hdrs = [
        "include/ros/console.h",
        "include/ros/console_backend.h",
        "include/rosconsole/macros_generated.h",
    ],
    strip_include_prefix = "//third_party/rosconsole/include",
    deps = [
        "//third_party/cpp_common",
    ],
)

cc_library(
    name = "rosconsole_print",
    srcs = [
        "src/rosconsole/impl/rosconsole_print.cpp",
    ],
    hdrs = [
        "include/ros/console.h",
        "include/ros/console_backend.h",
        "include/rosconsole/macros_generated.h",
    ],
    strip_include_prefix = "//third_party/rosconsole/include",
    deps = [
        "//third_party/cpp_common",
        "//third_party/rostime",
    ],
)

cc_library(
    name = "rosconsole_backend_interface",
    srcs = [
        "include/ros/console_backend.h",
        "src/rosconsole/rosconsole_backend.cpp",
    ],
    strip_include_prefix = "//third_party/rosconsole/include",
    deps = [
        ":rosconsole_print",  # TODO: use a select here to switch between glog/print
        "//third_party/cpp_common",
    ],
)

cc_library(
    name = "rosconsole",
    srcs = [
        "src/rosconsole/rosconsole.cpp",
    ],
    hdrs = [
        "include/ros/assert.h",
        "include/ros/console.h",
        "include/ros/console_backend.h",
        "include/ros/static_assert.h",
        "include/rosconsole/macros_generated.h",
    ],
    strip_include_prefix = "//third_party/rosconsole/include",
    visibility = ["//visibility:public"],
    deps = [
        ":rosconsole_backend_interface",
        "//third_party/cpp_common",
    ],
)
