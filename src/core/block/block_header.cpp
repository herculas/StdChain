#include "core/block/block_header.h"

#include <iostream>
#include <sstream>

#include "util/hash/sha256.h"

BlockHeader::BlockHeader(): version(0), time(0), bits(0), nonce(0) {
    this->hashPrevBlock.setNull();
    this->hashMerkleRoot.setNull();
}

bool BlockHeader::isNull() const {
    return this->bits == 0;
}

Blob256 BlockHeader::getHash() const {
    std::stringstream stream;
    stream << this->version
           << this->hashPrevBlock.getHex()
           << this->hashMerkleRoot.getHex()
           << this->time
           << this->bits
           << this->nonce;
    return util::hash::sha256(stream.str());
}

int64_t BlockHeader::getBlockTime() const {
    return (int64_t) this->time;
}
