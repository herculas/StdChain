#ifndef STDCHAIN_CORE_BLOCK_H
#define STDCHAIN_CORE_BLOCK_H

#include "core/block_header.h"

#include <string>

class Block {

public:
    BlockHeader header;

    // network and disk, 在網路中分發並存儲於磁碟中
    // TODO: transactions vector

    // memory only, 僅存儲於記憶體中
    mutable bool checked;

public:
    Block();
    explicit Block(const BlockHeader &header);
    BlockHeader getHeader() const;
    std::string toString() const;
};


#endif //STDCHAIN_CORE_BLOCK_H
