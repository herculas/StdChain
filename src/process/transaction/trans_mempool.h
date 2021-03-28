#ifndef STDCHAIN_PROCESS_TRANSACTION_MEMPOOL_H
#define STDCHAIN_PROCESS_TRANSACTION_MEMPOOL_H

#include <atomic>
#include "util/concurrent/sync.h"

class TxMemPool {

protected:
    const int32_t checkRatio;
    std::atomic<uint32_t> transactionsUpdated;
    // TODO: BlockPolicyEstimator *minerPolicyEstimator;
};


#endif //STDCHAIN_PROCESS_TRANSACTION_MEMPOOL_H
