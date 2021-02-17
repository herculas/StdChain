#ifndef STDCHAIN_CORE_BLOCK_H
#define STDCHAIN_CORE_BLOCK_H

#include <string>
#include <vector>
#include "block_header.h"
#include "core/transaction/transaction.h"

class Block {

public:
    BlockHeader header;
    std::vector<TransactionRef> vTx;
    mutable bool checked;

public:
    Block();
    explicit Block(const BlockHeader &header);
    BlockHeader getHeader() const;
    std::string toString() const;
};


#endif //STDCHAIN_CORE_BLOCK_H
