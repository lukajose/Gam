#include <iostream>
#include <sstream>  
#include "blockchain.h"

using namespace std;
int main() {
    Blockchain bChain = Blockchain();
    // cout << "Mining block 1 .. " << endl;
    // bChain + Block(1,"Block 1 data");

    // cout << "Mining Block 2 .." << endl;
    // bChain + Block(2,"Block 2 data");

    // cout << "Mining block 3 ..." << endl;
    // bChain + Block(3, "Block 3 data");

    
    for(int i = 0; i < 20; ++i ) {
        stringstream ss;
        ss << i;
        cout << "Mining block " + ss.str() + " ..." << endl;
        bChain + Block(i,"Block "+ ss.str() +" data");
    }

    bChain.printBlocks();

    return 0;
}