cc_library(
    name = "chain",
    srcs = ["block.cpp","blockchain.cpp","sha256.cpp"],
    hdrs = ["block.h","blockchain.h","sha256.h"],
)

cc_library(
    name = "mempool",
    srcs = ["mempool.cpp"],
    hdrs = ["mempool.h"],
    defines = ["BAZEL_BUILD"],
    deps = ["//proto:cppGamConcensusGrpclib"]
)
cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":mempool",
        ":chain",
    ],
)
