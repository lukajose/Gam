// Logic and data behind the server's behavior.

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
#include "proto/GamConcensus.grpc.pb.h"
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
// this is the low level implementation of the grpc with proto files
class ConcencusServiceImpl: public Concencus::Service  {
  Status newBlock(ServerContext* context, const Block* b,ConStatus* reply);
  Status TransactionSubs(ServerContext* context,const Empty * m, ServerWriter<Transaction> *stream);
};



// the class will be used as an interface of ConcensusServiceImpl, higher level usage
class grpcServer {
    public:
        void RunServer();
};