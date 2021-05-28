
# BUILD.bazel
# load("@rules_proto_grpc//cpp:defs.bzl", "cpp_proto_library")

proto_library(
    name = "GamConsensus",
    srcs = ["GamConsensus.proto"],
    visibility = ["//visibility:public"],
)

load("@rules_proto_grpc//cpp:defs.bzl", "cpp_proto_compile","cpp_proto_library")
cpp_proto_compile(
    name = "cppGamConsensus",
    protos = [":GamConsensus"],

)
cpp_proto_library(
    name = "cppGamConsensuslib",
    protos = [":GamConsensus"],

)


load("@rules_proto_grpc//cpp:defs.bzl", "cpp_grpc_compile","cpp_grpc_library")
cpp_grpc_library(
    name = "cppGamConsensusGrpclib",
    protos = [":GamConsensus"],
    visibility = ["//visibility:public"],
    deps = [":cppGamConsensuslib"],
)

cpp_grpc_compile(
    name = "cppGamConsensusGrpc",
    protos = [":GamConsensus"],
    visibility = ["//visibility:public"],
)

