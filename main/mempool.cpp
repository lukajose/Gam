#include <iostream>
#include "mempool.h"
#include <mutex>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <unistd.h>
#ifdef BAZEL_BUILD
#include "proto/GamConcensus.grpc.pb.h"
#include "concencus/serverConcensus.h"
#else
#include "GamConcensus.grpc.pb.h"
#endif
#define TRUE   1 
#define FALSE  0 
#define PORT 8888



MemPool::MemPool() {
    std::cout << "init pool " << std::endl;
};

int MemPool::listenTransactions() {

};


void MemPool::printTransactions() {
  while(!this->transactions.empty()) {
    Transaction t = this->transactions.top();
    this->transactions.pop();
    std::cout << "===== Transaction amout: " << t.Gam << " ============ " << std::endl;
    std::cout << "from:" << t.from << std::endl;
    std::cout << "to:" << t.to << std::endl;
  }
}


void MemPool::operator+(Transaction * t) {
  // add transaction class to priority queue
  this->transactions.push(*t);
};


