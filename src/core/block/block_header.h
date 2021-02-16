#ifndef STDCHAIN_CORE_BLOCK_HEADER_H
#define STDCHAIN_CORE_BLOCK_HEADER_H

#include <vector>
#include "type/blob/blob_256.h"
#include "util/serialize/serialize.h"

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
    void serialize(Stream &stream) const {
        static_assert(std::is_same<const BlockHeader &, decltype(*this)>::value, "serialize type mismatch");
        util::serialize::serializeMany(stream,
                                       this->version,
                                       this->hashPrevBlock,
                                       this->hashMerkleRoot,
                                       this->time,
                                       this->bits,
                                       this->nonce);
    }

};


#endif //STDCHAIN_CORE_BLOCK_HEADER_H
