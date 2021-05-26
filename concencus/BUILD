
cc_library(
    name = "concensus",
    srcs = ["concencusServer.cpp"],
    hdrs = ["concencusServer.h"],
)

cc_binary(
    name = "serverGrpc",
    srcs = ["greeter_server.cpp"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "//proto:cppGamConcensusGrpclib",
        ":concencus" 
    ],
)

cc_binary(
    name = "greeter_client",
    srcs = ["greeter_client.cpp"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "//proto:cppGamConcensusGrpclib",
    ],
)