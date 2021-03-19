#ifndef STDCHAIN_CORE_CHAIN_H
#define STDCHAIN_CORE_CHAIN_H

#include <vector>
#include "core/block/block_locator.h"
#include "core/chain/block_index.h"

class Chain {

private:
    std::vector<BlockIndex *> chain;

public:
    [[nodiscard]] BlockIndex *genesis() const;
    [[nodiscard]] BlockIndex *tip() const;
    BlockIndex *operator[](int32_t height) const;
    bool contains(const BlockIndex *index) const;
    BlockIndex *next(const BlockIndex *index) const;
    [[nodiscard]] int32_t height() const;
    void setTip(BlockIndex *index);
    BlockLocator getLocator(const BlockIndex *index = nullptr) const;
    const BlockIndex *findFork(const BlockIndex *index) const;
    [[nodiscard]] BlockIndex *findEarliestAtLeast(int64_t time, int32_t height) const;

};

#endif //STDCHAIN_CHAIN_H
