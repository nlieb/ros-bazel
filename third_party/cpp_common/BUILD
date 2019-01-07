licenses(["notice"])  # BSD

cc_library(
    name = "cpp_common",
    srcs = ["src/debug.cpp"],
    hdrs = glob(["include/ros/*.h"]),
    copts = [
        "-DHAVE_CXXABI_H=1",
        "-DHAVE_EXECINFO_H=1",
        "-DHAVE_GLIBC_BACKTRACE",
    ],
    strip_include_prefix = "//third_party/cpp_common/include",
    visibility = ["//visibility:public"],
)
