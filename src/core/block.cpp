#include <sstream>
#include "core/block.h"

Block::Block() : header(), checked(false) {
    // TODO: transactions
}

Block::Block(const BlockHeader &header) : header(), checked(false) {
    // TODO: transactions
}

BlockHeader Block::getHeader() const {
    return this->header;
}

std::string Block::toString() const {
    std::stringstream stream;
    stream << this->getHeader().getHash().toString();
    return stream.str();
}
