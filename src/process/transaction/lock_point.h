#ifndef STDCHAIN_PROCESS_TRANSACTION_LOCK_POINT_H
#define STDCHAIN_PROCESS_TRANSACTION_LOCK_POINT_H

#include "core/chain/block_index.h"

class LockPoints {

public:
    int32_t height;
    int64_t time;
    BlockIndex *maxInputBlock;

public:
    LockPoints();

};

LockPoints::LockPoints(): height{0}, time{0}, maxInputBlock{nullptr} {}

#endif //STDCHAIN_PROCESS_TRANSACTION_LOCK_POINT_H
