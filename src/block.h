#include <iostream>
#include <cstdint>
using namespace std;
class Block {
    public:
        string _sHash;
        string sPrevHash;
        Block(uint32_t nIndexIn,const string &sDataIn); // constructor
        string GetHash();
        void MineBlock(uint32_t nDifficulty);
    private:
        uint32_t _nIndex;
        int64_t _nNonce;
        string _sData;
        time_t _tTime;
        string _CalculateHash() const;
};