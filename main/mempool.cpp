#include <iostream>
#include "mempool.h"
#include <mutex>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#ifdef BAZEL_BUILD
#include "proto/GamConcensus.grpc.pb.h"
#else
#include "GamConcensus.grpc.pb.h"
#endif
#define TRUE   1 
#define FALSE  0 
#define PORT 8888

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using proto::Greeter;
using proto::HelloReply;
using proto::HelloRequest;


/// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Greeter::Service {
  public:
    Mempool pool(100);
    Status SayHello(ServerContext* context, const HelloRequest* request,
                    HelloReply* reply) override {
      std::string prefix("Hello ");
      reply->set_message(prefix + request->name());
      return Status::OK;
    }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  GreeterServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
};



MemPool::MemPool(int connSize) {
    this->maxClients = connSize;
    this->clientSockets = new int[connSize];
    memset(this->clientSockets,0,connSize);
    this->clientIndex = 0;
};

int MemPool::listenTransactions() {
    RunServer();
};

void MemPool::operator+(Transaction * t) {
  // add transaction class to priority queue
  cout << "TODO" << endl;
};