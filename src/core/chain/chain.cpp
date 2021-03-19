#include "core/chain/chain.h"

#include <algorithm>
#include <utility>

BlockIndex *Chain::genesis() const {
    return !this->chain.empty() ? this->chain[0] : nullptr;
}

BlockIndex *Chain::tip() const {
    return !this->chain.empty() ? this->chain[this->chain.size() - 1] : nullptr;
}

BlockIndex *Chain::operator[](int32_t height) const {
    if (height < 0 || height > this->chain.size()) return nullptr;
    return this->chain[height];
}

bool Chain::contains(const BlockIndex *index) const {
    return (*this)[index->height] == index;
}

BlockIndex *Chain::next(const BlockIndex *index) const {
    if (this->contains(index)) return (*this)[index->height + 1];
    return nullptr;
}

int32_t Chain::height() const {
    return this->chain.size() - 1;
}

void Chain::setTip(BlockIndex *index) {
    if (index == nullptr) {
        this->chain.clear();
        return;
    }
    this->chain.resize(index->height + 1);
    while (index && this->chain[index->height] != index) {
        this->chain[index->height] = index;
        index = index->prevBlock;
    }
}

BlockLocator Chain::getLocator(const BlockIndex *index) const {
    int32_t step = 1;
    std::vector<Blob256> have;
    have.reserve(32);
    if (!index) index = this->tip();
    while (index) {
        have.push_back(index->getBlockHash());
        if (index->height == 0) break;
        int32_t height = std::max(index->height - step, 0);
        if (this->contains(index))
            index = (*this)[height];
        else
            index = index->getAncestor(height);
        if (have.size() > 10)
            step *= 2;
    }
    return BlockLocator(have);
}

const BlockIndex *Chain::findFork(const BlockIndex *index) const {
    if (index == nullptr) return nullptr;
    if (index->height > this->height())
        index = index->getAncestor(this->height());
    while (index && !this->contains(index)) index = index->prevBlock;
    return index;
}

BlockIndex *Chain::findEarliestAtLeast(int64_t time, int32_t height) const {
    std::pair<int64_t, int32_t> blockParams = std::make_pair(time, height);
    auto lower = std::lower_bound(this->chain.begin(), this->chain.end(), blockParams,
                                  [](BlockIndex *index, const std::pair<int64_t, int32_t> &blockParams) -> bool {
                                      return index->getBlockTimeMax() < blockParams.first ||
                                             index->height < blockParams.second;
                                  });
    return (lower == this->chain.end() ? nullptr : *lower);
}
