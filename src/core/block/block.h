#ifndef STDCHAIN_CORE_BLOCK_H
#define STDCHAIN_CORE_BLOCK_H

#include <string>
#include <vector>
#include "boost/serialization/vector.hpp"
#include "core/block/block_header.h"
#include "core/transaction/trans_ref.h"

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

private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &archive, unsigned int archiveVersion);
};

template<typename Archive>
void Block::serialize(Archive &archive, unsigned int archiveVersion) {
    archive & this->header;
    archive & this->vTx;
    archive & this->checked;
}

#endif //STDCHAIN_CORE_BLOCK_H
