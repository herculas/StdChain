#ifndef STDCHAIN_CORE_BLOCK_HEADER_H
#define STDCHAIN_CORE_BLOCK_HEADER_H

#include <vector>
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
    [[nodiscard]] int64_t getBlockTime() const;

public:
    template<typename Stream>
    void serialize(Stream &stream) const;

};

template<typename Stream>
void BlockHeader::serialize(Stream &stream) const {
    // TODO
    static_assert(std::is_same<const BlockHeader &, decltype(*this)>::value, "serialize type mismatch");
}

#endif //STDCHAIN_CORE_BLOCK_HEADER_H
