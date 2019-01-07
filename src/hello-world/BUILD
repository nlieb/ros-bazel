cc_binary(
    name = "hello-world",
    srcs = [
        "hello-world.cc",
        "//third_party/std_msgs:Bool",
    ],
    features = ["fully_static_link"],
    deps = [
        "//third_party/cpp_common",
        "//third_party/roscpp_serialization",
        "//third_party/roscpp_traits",
        #        "//third_party/std_msgs:std_msgs_bool",
    ],
)
