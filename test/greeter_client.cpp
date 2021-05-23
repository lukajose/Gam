
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <grpcpp/grpcpp.h>
#include <vector>
#include <sstream>
#include <unistd.h>
#ifdef BAZEL_BUILD
#include "proto/GamConcensus.grpc.pb.h"
#else
#include "GamConcensus.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReader;
using proto::Concencus;
using proto::Empty;
using proto::Block;

class ConcensusClient {
 public:
  ConcensusClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  void SayHello(const std::string& user) {
    // Data we are sending to the server.

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    std::shared_ptr<ClientReaderWriter<HelloRequest,HelloReply> > stream(
        stub_->SayHello(&context));
    // The actual RPC.
    std::thread writer([stream]() {
        
        for(int i = 0; i < 11; i++) {
          HelloRequest request;
          std::stringstream ss;
          std::string is = "Luka";
          ss << i;
          ss >> is;
          request.set_name(is);
          std::cout << "Sending message: " + is << std::endl;
          stream->Write(request);
          sleep(3);
        }
        stream->WritesDone();
    });
    HelloReply reply;
    while(stream->Read(&reply)) {
      std::cout << "Response: " << reply.message() << std::endl;
    }
    writer.join();
    grpc::Status status = stream->Finish();
    if (!status.ok()) {
      std::cout << "RouteChat rpc failed." << std::endl;
    } else {
      std::cout << "Closing connection all good!" << std::endl;
    };
    
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint specified by
  // the argument "--target=" which is the only expected argument.
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).
  std::string target_str = "localhost:50051";
  GreeterClient greeter(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  std::string user("World by Luka!");
  greeter.SayHello(user);

  return 0;
}