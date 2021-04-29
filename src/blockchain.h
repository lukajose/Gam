#include <vector>
#include "block.h"
#include <cstdint>
using namespace std;
class Blockchain {
    public:
        Blockchain();
        void operator+(Block bNew);
    private:
        uint32_t _nDifficulty;
        std::vector<Block> _vChain;
        Block _GetLastBlock() const;  

};