# from https://github.com/ros/gencpp
# commit b41ee3060badd660662e21cd9d4f81971c87a420

licenses(["notice"])  # BSD

py_library(
    name = "gencpp",
    srcs = [
        "src/gencpp/__init__.py",
    ],
    imports = ["src"],
    visibility = ["//visibility:public"],
    deps = [
        "//third_party/py/genmsg",
    ],
)

py_binary(
    name = "gen_cpp",
    srcs = [
        "scripts/gen_cpp.py",
    ],
    data = [
        "scripts/msg.h.template",
        "scripts/srv.h.template",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//third_party/py/genmsg",
        "gencpp"
    ],
)
