cc_library(
    name = "chain",
    srcs = ["block.cpp","blockchain.cpp","mempool.cpp","sha256.cpp"],
    hdrs = ["block.h","blockchain.h","mempool.h","sha256.h"],
)
cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        ":chain",
        ":cppGamConcensusGrpc"
    ],
)
