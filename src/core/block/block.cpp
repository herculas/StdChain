#include "core/block/block.h"

#include <sstream>

Block::Block() : header(), checked(false) {
    this->vTx.clear();
}

Block::Block(const BlockHeader &header) : header(header), checked(false) {
    this->vTx.clear();
}

BlockHeader Block::getHeader() const {
    return this->header;
}

std::string Block::toString() const {
    std::stringstream stream;
    stream << this->getHeader().getHash().toString();
    return stream.str();
}
