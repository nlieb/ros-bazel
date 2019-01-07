licenses(["notice"])  # BSD

cc_library(
    name = "xmlrpcpp",
    srcs = [
        "src/XmlRpcClient.cpp",
        "src/XmlRpcDispatch.cpp",
        "src/XmlRpcServer.cpp",
        "src/XmlRpcServerConnection.cpp",
        "src/XmlRpcServerMethod.cpp",
        "src/XmlRpcSocket.cpp",
        "src/XmlRpcSource.cpp",
        "src/XmlRpcUtil.cpp",
        "src/XmlRpcValue.cpp",
    ],
    hdrs = [
        "include/xmlrpcpp/XmlRpc.h",
        "include/xmlrpcpp/XmlRpcClient.h",
        "include/xmlrpcpp/XmlRpcDecl.h",
        "include/xmlrpcpp/XmlRpcDispatch.h",
        "include/xmlrpcpp/XmlRpcException.h",
        "include/xmlrpcpp/XmlRpcServer.h",
        "include/xmlrpcpp/XmlRpcServerConnection.h",
        "include/xmlrpcpp/XmlRpcServerMethod.h",
        "include/xmlrpcpp/XmlRpcSocket.h",
        "include/xmlrpcpp/XmlRpcSource.h",
        "include/xmlrpcpp/XmlRpcUtil.h",
        "include/xmlrpcpp/XmlRpcValue.h",
        "include/xmlrpcpp/base64.h",
    ],
    strip_include_prefix = "//third_party/xmlrpcpp/include",
    visibility = ["//visibility:public"],
    deps = [
        "//third_party/cpp_common",
        "//third_party/libb64",
        "//third_party/rostime",
    ],
)
