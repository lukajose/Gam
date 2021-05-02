#include "blockchain.h"

Blockchain::Blockchain() {
    _vChain.emplace_back(Block(0, "Genesis Block"));
    _nDifficulty = 4;
}

void Blockchain::operator+(Block bNew) {
    bNew.sPrevHash = _GetLastBlock()._sHash;
    bNew.MineBlock(_nDifficulty);
    _vChain.push_back(bNew);
}

void Blockchain::printBlocks() {
    cout << "======= Your Chain =======" << endl;
    int i = 0;
    for(auto block = _vChain.begin(); block != _vChain.end();++block) {
        cout << "block[" << i << "]:" << block->_sHash << endl;
        ++i;
    };
};


Block Blockchain::_GetLastBlock() const {
    return _vChain.back();
}

bool Blockchain::_IsChainValid() {
    
    return true;
};