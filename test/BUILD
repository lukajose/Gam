
cc_binary(
    name = "greeter_server",
    srcs = ["greeter_server.cpp"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "//proto:cppGamConcensusGrpclib", 
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