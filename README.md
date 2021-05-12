# Custom Crypto Currency

A custom crypto currency in C++. The currency uses a similar p2p protocol as bitcoin. Instead of raw tcp the currency uses grpc.
The concencus mechanism used is proof of work. More on this later.

## Dependencies

grpc uses proto 3 to install the compiler follow the instructions:

- https://github.com/protocolbuffers/protobuf/blob/master/src/README.md


## Compiling

You will need bazel to run the project to install follow the instructions:

- https://docs.bazel.build/versions/master/install.html

To compile grpc libraries and proto buffs:

```
bazel build :cppGamConcensusGrpc

```

Run using:

```
bazel run //:main/main
```