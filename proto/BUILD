proto_library(
    name = "GamConcensus",
    srcs = ["GamConcensus.proto"],
    deps = ["@com_google_protobuf//:any_proto"],
)

# BUILD.bazel
load("@rules_proto_grpc//cpp:defs.bzl", "cpp_proto_library")

cpp_proto_library(
    name = "concencus",
    protos = [":GamConcensus"],
    visibility = ["//src:__pkg__"],
)