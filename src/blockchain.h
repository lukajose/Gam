#include <vector>
#include "block.h"
#include <cstdint>
#include <set>
using namespace std;
class Blockchain {
    public:
        Blockchain();
        void operator+(Block bNew);
        void printBlocks();
        void replaceChain();

    private:
        uint32_t _nDifficulty;
        uint32_t _chainHeight;
        vector<Block> _vChain;
        Block _GetLastBlock() const;
        bool _IsChainValid();  
        set<string> nodes;
};