
cc_library(
    name = "consensus",
    srcs = ["grpcServer.cpp"],
    hdrs = ["grpcServer.h"],
    deps = ["//proto:cppGamConsensusGrpclib"],
)

cc_binary(
    name = "testServer",
    srcs = ["testServer.cpp"],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":consensus" 
    ],
)

cc_binary(
    name = "testClient",
    srcs = ["testClient.cpp"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "//proto:cppGamConsensusGrpclib",
    ],
)