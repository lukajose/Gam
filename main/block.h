#include <iostream>
#include <cstdint>
using namespace std;
class Block {
    public:
        string _sHash; // cryptographic hash
        string sPrevHash; // previous block hash
        Block(uint32_t nIndexIn,const string &sDataIn); // constructor
        string GetHash();
        void MineBlock(uint32_t nDifficulty);
    private:
        uint32_t _nIndex; // blockchain index
        int64_t _nNonce; // number used once
        string _sData; // data in block
        time_t _tTime; // timestamp in block
        string _CalculateHash() const;
};