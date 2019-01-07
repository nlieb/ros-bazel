licenses(["permissive"])

py_runtime(
    name = "python2_7_15",
    files = glob(
        [
            "x86_64-pc-linux-gnu/**",
        ],
        exclude = [
            "**/* *",
        ],
    ),
    interpreter = "x86_64-pc-linux-gnu/bin/python2.7",
    visibility = ["//visibility:public"],
)

alias(
    name = "python2",
    actual = ":python2_7_15",
    visibility = ["//visibility:public"],
)
