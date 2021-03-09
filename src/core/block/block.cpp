#include "core/block/block.h"

#include <sstream>
#include "boost/format.hpp"

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
    stream << boost::format("Block(hash=%s, version=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, time=%u, bits=%08x, nonce=%u, vtx=%u)\n")
            % this->getHeader().getHash().toString()
            % this->getHeader().version
            % this->getHeader().hashPrevBlock.toString()
            % this->getHeader().hashMerkleRoot.toString()
            % this->getHeader().time
            % this->getHeader().bits
            % this->getHeader().nonce
            % this->vTx.size();
//    for (const auto &tx : this->vTx)
//        stream << "    " << tx->toString() << "\n";
    return stream.str();
}
