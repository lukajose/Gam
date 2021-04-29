#include <cstdint>
#include <vector>
#include "block.h"
#include "sha256.h"
#include <sstream>
using namespace std;

Block::Block(uint32_t nIndexIn, const string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn) {
    _nNonce = -1;
    _tTime = time(nullptr);
    _sHash = "root";
}

// getter  method for returning the hash
string Block::GetHash() {
    return _sHash;
}

// this is where the mining block magic happens
/*
    a miner must create a crypto hash of the block that matches the requirements for a valid hash
    at that time, it needs to count the number of zeroes at the beginning og the hash, if number of zeros is equal
    to  or greater than the difficulty level set by the network block is valid;
    The process is called proof of work;
*/
void Block::MineBlock(uint32_t nDifficulty) {
    char cstr[nDifficulty + 1];
    for(uint32_t i =0; i< nDifficulty; ++i) {
        cstr[i] = '0';
    };
    // null terminator
    cstr[nDifficulty] = '\0';

    // type cast to string
    string str(cstr);

    do {
        _nNonce++;
        _sHash = _CalculateHash();
    } while (_sHash.substr(0,nDifficulty) != str);
    cout << "Block mined: " << _sHash << endl;
};

inline string Block::_CalculateHash() const {
    stringstream ss;
    ss << _nIndex << _tTime << _sData << _nNonce << sPrevHash;
    return sha256(ss.str());
};
