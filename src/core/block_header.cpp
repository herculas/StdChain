#include "core/block_header.h"
#include "type/hash/hash_writer.h"

BlockHeader::BlockHeader(): version(0), time(0), bits(0), nonce(0) {
    // TODO: Hash previous block
    // TODO: Hash Merkle root
}

bool BlockHeader::isNull() const {
    return this->bits == 0;
}

Blob256 BlockHeader::getHash() const {
    return serializeHash(*this);
}

int64_t BlockHeader::getBlockTime() const {
    return (int64_t) this->time;
}