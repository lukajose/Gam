#include <iostream>
#include <sstream>  
#include "blockchain.h"
#include "mempool.h"
#include <thread>
#include <unistd.h>
using namespace std;

void hello() {
    int i = 0;
    while(i < 100) {
        cout << i << endl;
        i++;
        sleep(2);
    };
};



int main() {
    Blockchain bChain = Blockchain();
    
    for(int i = 0; i < 20; ++i ) {
        stringstream ss;
        ss << i;
        cout << "Mining block " + ss.str() + " ..." << endl;
        bChain + Block(i,"Block "+ ss.str() +" data");
    }

    bChain.printBlocks();
    MemPool pool(100);
    std::thread t(hello);
    while(true) {
        cout << "another thread running" << endl;
        sleep(10);
    }
    t.join();

    return 1;
}