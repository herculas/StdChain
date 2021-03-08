#include "block_header.h"

BlockHeader::BlockHeader(): version(0), time(0), bits(0), nonce(0) {
    this->hashPrevBlock.setNull();
    this->hashMerkleRoot.setNull();
}

bool BlockHeader::isNull() const {
    return this->bits == 0;
}

Blob256 BlockHeader::getHash() const {
    // TODO
    return Blob256();
}

int64_t BlockHeader::getBlockTime() const {
    return (int64_t) this->time;
}
