#ifndef STDCHAIN_CORE_BLOCK_HEADER_H
#define STDCHAIN_CORE_BLOCK_HEADER_H

#include <vector>
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"
#include "type/blob/blob_256.h"

class BlockHeader {

public:
    int32_t version;
    Blob256 hashPrevBlock;
    Blob256 hashMerkleRoot;
    uint32_t time;
    uint32_t bits;
    uint32_t nonce;

public:
    BlockHeader();
    [[nodiscard]] bool isNull() const;
    [[nodiscard]] Blob256 getHash() const;
    [[nodiscard]] uint32_t getBlockTime() const;

private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &archive, uint32_t ver);
};

template<typename Archive>
void BlockHeader::serialize(Archive &archive, uint32_t ver) {
    archive & this->version;
    archive & this->hashPrevBlock;
    archive & this->hashMerkleRoot;
    archive & this->time;
    archive & this->bits;
    archive & this->nonce;
}

#endif //STDCHAIN_CORE_BLOCK_HEADER_H
