#include "core/chain/block_index.h"
#include <algorithm>
#include <sstream>
#include "boost/format.hpp"

BlockIndex::BlockIndex() : hashBlock{nullptr}, prevBlock{nullptr}, skipBlock{nullptr},
                           height{0}, file{0}, dataPos{0}, undoPos{0}, chainWork{},
                           tx{0}, chainTx{0}, status{0}, version{0}, hashMerkleRoot{},
                           time{0}, bits{0}, nonce{0}, sequenceId{0}, timeMax{0} {}

BlockIndex::BlockIndex(const BlockHeader &header) : hashBlock{nullptr}, prevBlock{nullptr}, skipBlock{nullptr},
                                                    height{0}, file{0}, dataPos{0}, undoPos{0}, chainWork{},
                                                    tx{0}, chainTx{0}, status{0},
                                                    version{header.version}, hashMerkleRoot{header.hashMerkleRoot},
                                                    time{header.time}, bits{header.bits}, nonce{header.nonce},
                                                    sequenceId{0}, timeMax{0} {}

FlatFilePos BlockIndex::getBlockPos() const {
    FlatFilePos res;
    if (this->status == BlockStatus::BLOCK_HAVE_DATA) {
        res.file = this->file;
        res.pos = this->dataPos;
    }
    return res;
}

FlatFilePos BlockIndex::getUndoPos() const {
    FlatFilePos res;
    if (this->status == BlockStatus::BLOCK_HAVE_UNDO) {
        res.file = this->file;
        res.pos = this->undoPos;
    }
    return res;
}

BlockHeader BlockIndex::getBlockHeader() const {
    BlockHeader header;
    header.version = this->version;
    header.hashMerkleRoot = this->hashMerkleRoot;
    header.time = this->time;
    header.bits = this->bits;
    header.nonce = this->nonce;
    if (this->prevBlock) header.hashPrevBlock = this->prevBlock->getBlockHash();
    return header;
}

Blob256 BlockIndex::getBlockHash() const {
    return *this->hashBlock;
}

bool BlockIndex::isValid(BlockStatus upTo) const {
    assert(!(upTo & ~BlockStatus::BLOCK_VALID_MASK));
    if (this->status & BlockStatus::BLOCK_FAILED_MASK)
        return false;
    return ((this->status & BlockStatus::BLOCK_VALID_MASK) >= upTo);
}

bool BlockIndex::haveTransactionsDownloaded() const {
    return this->chainTx != 0;
}

bool BlockIndex::raiseValidity(BlockStatus upTo) {
    assert(!(upTo & ~BlockStatus::BLOCK_VALID_MASK));
    if (this->status & BlockStatus::BLOCK_FAILED_MASK)
        return false;
    if ((this->status & BlockStatus::BLOCK_VALID_MASK) < upTo) {
        this->status = (this->status & ~BlockStatus::BLOCK_VALID_MASK) | upTo;
        return true;
    }
    return false;
}

int64_t BlockIndex::getBlockTime() const {
    return (int64_t) this->time;
}

int64_t BlockIndex::getBlockTimeMax() const {
    return (int64_t) this->timeMax;
}

int64_t BlockIndex::getMedianTimePast() const {
    const int32_t MEDIAN_TIME_SPAN = 11;
    int64_t median[MEDIAN_TIME_SPAN];
    int64_t *begin = &median[MEDIAN_TIME_SPAN];
    int64_t *end = &median[MEDIAN_TIME_SPAN];
    const BlockIndex *index = this;
    for (int32_t i = 0; i < MEDIAN_TIME_SPAN && index; i++, index = index->prevBlock) {
        *(--begin) = index->getBlockTime();
    }
    std::sort(begin, end);
    return begin[(end - begin) / 2];
}

int32_t invertLowestOne(int32_t n) {
    return n & (n - 1);
}

int32_t getSkipHeight(int32_t height) {
    if (height < 2) return 0;
    return (height & 1) ? invertLowestOne(invertLowestOne(height - 1)) + 1 : invertLowestOne(height);
}

void BlockIndex::buildSkip() {
    if (this->prevBlock)
        this->skipBlock = this->prevBlock->getAncestor(getSkipHeight(this->height));
}

BlockIndex *BlockIndex::getAncestor(int32_t ancHeight) {
    return const_cast<BlockIndex *>(static_cast<const BlockIndex *>(this)->getAncestor(ancHeight));
}

const BlockIndex *BlockIndex::getAncestor(int32_t ancHeight) const {
    if (ancHeight > this->height || ancHeight < 0)
        return nullptr;
    const BlockIndex *indexWalk = this;
    int32_t heightWalk = this->height;
    while (heightWalk > ancHeight) {
        int32_t heightSkip = getSkipHeight(heightWalk);
        int32_t heightSkipPrev = getSkipHeight(heightWalk - 1);
        if (indexWalk->skipBlock != nullptr && (heightSkip == ancHeight || (heightSkip > ancHeight &&
                                                                            !(heightSkipPrev < heightSkip - 2 &&
                                                                              heightSkipPrev >= ancHeight)))) {
            indexWalk = indexWalk->skipBlock;
            heightWalk = heightSkip;
        } else {
            assert(indexWalk->prevBlock);
            indexWalk = indexWalk->prevBlock;
            heightWalk--;
        }
    }
    return indexWalk;
}

std::string BlockIndex::toString() const {
    std::stringstream stream;
    stream << boost::format("BlockIndex(prev=%p, height=%d, merkle=%s, hashBlock=%s)")
              % this->prevBlock
              % this->height
              % this->hashMerkleRoot.toString()
              % this->getBlockHash().toString();
    return stream.str();
}
