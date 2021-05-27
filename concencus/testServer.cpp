
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include "grpcServer.h"

int main(int argc, char** argv) {
  std::thread t(&grpcServer::RunServer,grpcServer());
  std::cout << "Getting there! :)" << std::endl;
  t.join();
  return 0;
}
