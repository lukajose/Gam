#include <iostream>
#include <sstream>  
#include "blockchain.h"
#include "mempool.h"

using namespace std;
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
    int status = pool.listenTransactions();
    cout << "Status:" << status << endl;
    

    return 1;
}