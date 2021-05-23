
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <unistd.h>
#ifdef BAZEL_BUILD
#include "proto/GamConcensus.grpc.pb.h"
#else
#include "GamConcensus.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::ServerWriter;
using proto::Concencus;
using proto::ConStatus;
using proto::Transaction;
using proto::Block;
using proto::Empty;

// Logic and data behind the server's behavior.
class ConcencusServiceImpl: public Concencus::Service  {
  Status newBlock(ServerContext* context, const Block* b,
                  ConStatus* reply)  {
    std::cout << "Received Block, hash:" << b->hash() << " nonce:" << b->nonce() << std::endl;
    reply->set_added(true);
    return Status::OK;
  }
  Status TransactionSub(ServerContext* context,const Empty * m, ServerWriter<Transaction> *stream)   {
    for(int i = 0; i < 100 ; i++) {
      proto::Transaction t;
      t.set_from("Luka");
      t.set_to("Gam");
      t.set_amount(i +2);
      stream->Write(t);
      sleep(3);
    };
    return Status::OK;
  };
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  ConcencusServiceImpl service;

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
}

int main(int argc, char** argv) {
  std::thread t(RunServer);
  std::cout << "Getting there! :)" << std::endl;
  t.join();
  return 0;
}
