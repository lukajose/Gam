
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
using proto::ConStatus;
using proto::Transaction;

class ConcensusClient {
 public:
  ConcensusClient(std::shared_ptr<Channel> channel)
      : stub_(Concencus::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  void TransactionReader() {
    // Data we are sending to the server.
    std::cout << "starting reading .. " << std::endl;
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    proto::Empty e;
    std::shared_ptr<ClientReader<Transaction> >stream(
        stub_->TransactionSubs(&context,e)
    );
    // The actual RPC.
    Transaction t;
    while(stream->Read(&t)) {
      std::cout << "Transaction Response: from: " << t.from() << " to:" << t.to() << " amount:" << t.amount() << std::endl;
    };
    Status status = stream->Finish();
    if (!status.ok()) {
      std::cout << "Transaction stream failed" << std::endl;
    } else {
      std::cout << "Closing connection all good!" << std::endl;
    };
  };
  Block MakeBlock(std::string hash,uint nonce,std::string merkle) {
    Block b;
    b.set_hash(hash);
    b.set_nonce(nonce);
    b.set_merkletreehash(merkle);
    return b;
  };
  void SendBlock() {
    Block b = MakeBlock("random12312sadasda@@#!",10,"12312asdakslda!!@#ASD");
    ConStatus conn;
    newBlock(b,&conn);
    std::cout << "ConStatus in send block " << conn.added() << std::endl;
  };

 private:
  std::unique_ptr<Concencus::Stub> stub_;
  bool newBlock(const Block &b, ConStatus * conn) {
    std::cout << "new block sending .. " << std::endl;
    ClientContext context;
    Status status = stub_->newBlock(&context,b,conn);
    if(!status.ok()) {
      std::cout << "Something went wrong calling the rpc new Block" << std::endl;
      return false;
    } else {
      std::cout << "new Block:" << "response:" << conn->added() << std::endl;
    }
    return true;
  };
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint specified by
  // the argument "--target=" which is the only expected argument.
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).
  std::string target_str = "localhost:50051";
  ConcensusClient cc(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials())
    );
  cc.TransactionReader();
  cc.SendBlock();
  return 0;
}