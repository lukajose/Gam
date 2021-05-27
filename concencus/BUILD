
cc_library(
    name = "concensus",
    srcs = ["grpcServer.cpp"],
    hdrs = ["grpcServer.h"],
    deps = ["//proto:cppGamConcensusGrpclib"],
)

cc_binary(
    name = "testServer",
    srcs = ["testServer.cpp"],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":concensus" 
    ],
)

cc_binary(
    name = "testClient",
    srcs = ["testClient.cpp"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "//proto:cppGamConcensusGrpclib",
    ],
)