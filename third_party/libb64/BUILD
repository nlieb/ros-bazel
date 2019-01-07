licenses(["notice"])  # BSD

cc_library(
    name = "libb64",
    srcs = [
        "src/cdecode.c",
        "src/cencode.c",
    ],
    hdrs = [
        "include/b64/cdecode.h",
        "include/b64/cencode.h",
        "include/b64/decode.h",
        "include/b64/encode.h",
    ],
    strip_include_prefix = "//third_party/libb64/include",
    visibility = ["//visibility:public"],
)
