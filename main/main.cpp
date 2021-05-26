#include <iostream>
#include <sstream>  
#include "blockchain.h"
#include "mempool.h"
#include <thread>
#include <unistd.h>




int main() {
    
    MemPool pool;
    std::thread t([&pool](){
        pool.listenTransactions();
    });
    // while(true) {
    //     cout << "another thread running" << endl;
    //     sleep(10);
    // }
    Blockchain bChain = Blockchain();
    
    for(int i = 0; i < 20; ++i ) {
        stringstream ss;
        ss << i;
        std::cout << "Mining block " + ss.str() + " ..." << std::endl;
        bChain + Block(i,"Block "+ ss.str() +" data");
    }
    bChain.printBlocks();
    t.join();

    return 1;
}