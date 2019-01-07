# from https://github.com/ros/genmsg
# commit 42e364661025b8f3d51486dc513d9e29cbd308da

licenses(["notice"])  # BSD

py_library(
    name = "genmsg",
    srcs = [
        "genmsg/__init__.py",
        "genmsg/base.py",
        "genmsg/command_line.py",
        "genmsg/deps.py",
        "genmsg/gentools.py",
        "genmsg/msg_loader.py",
        "genmsg/msgs.py",
        "genmsg/names.py",
        "genmsg/srvs.py",
        "genmsg/template_tools.py",
    ],
    imports = ["."],
    visibility = ["//visibility:public"],
    deps = ["//third_party/py/em"],
)

TEST_FILES = glob(["test/files/**/*"])

MSG_FILES = glob(["test/md5tests/**/*"])

py_test(
    name = "test_genmsg_base",
    srcs = ["test/test_genmsg_base.py"],
    data = TEST_FILES,
    deps = [":genmsg"],
)

py_test(
    name = "test_genmsg_command_line",
    srcs = ["test/test_genmsg_command_line.py"],
    data = TEST_FILES,
    deps = [":genmsg"],
)

py_test(
    name = "test_genmsg_gentools",
    srcs = ["test/test_genmsg_gentools.py"],
    data = TEST_FILES + MSG_FILES,
    deps = [":genmsg"],
)

py_test(
    name = "test_genmsg_msg_loader",
    srcs = ["test/test_genmsg_msg_loader.py"],
    data = TEST_FILES,
    deps = [":genmsg"],
)

py_test(
    name = "test_genmsg_msgs",
    srcs = ["test/test_genmsg_msgs.py"],
    data = TEST_FILES,
    deps = [":genmsg"],
)

py_test(
    name = "test_genmsg_names",
    srcs = ["test/test_genmsg_names.py"],
    data = TEST_FILES,
    deps = [":genmsg"],
)

py_test(
    name = "test_genmsg_srvs",
    srcs = ["test/test_genmsg_srvs.py"],
    data = TEST_FILES,
    deps = [":genmsg"],
)
