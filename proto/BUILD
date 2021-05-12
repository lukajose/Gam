
# BUILD.bazel
# load("@rules_proto_grpc//cpp:defs.bzl", "cpp_proto_library")

proto_library(
    name = "GamConcensus",
    srcs = ["GamConcensus.proto"],
    visibility = ["//visibility:public"],
)

load("@rules_proto_grpc//cpp:defs.bzl", "cpp_proto_compile")
cpp_proto_compile(
    name = "cppGamConcensus",
    protos = [":GamConcensus"],

)

load("@rules_proto_grpc//cpp:defs.bzl", "cpp_grpc_compile","cpp_grpc_library")
cpp_grpc_library(
    name = "cppGamConcensusGrpclib",
    protos = [":GamConcensus"],
    visibility = ["//visibility:public"],
)

cpp_grpc_compile(
    name = "cppGamConcensusGrpc",
    protos = [":GamConcensus"],
    visibility = ["//visibility:public"],
)

