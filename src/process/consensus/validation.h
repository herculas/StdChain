#ifndef STDCHAIN_PROCESS_CONSENSUS_VALIDATION_H
#define STDCHAIN_PROCESS_CONSENSUS_VALIDATION_H

#include "core/block/block.h"
#include "core/transaction/transaction.h"

namespace process::consensus {

    static inline int64_t getTransactionWeight(const Transaction &tx) {
        // TODO
        return 0;
    }

    static inline int64_t getBlockWeight(const Block &block) {
        // TODO
        return 0;
    }

    static inline int64_t getTransactionInputWeight(const TxIn &txIn) {
        // TODO
        return 0;
    }

} // namespace process::consensus


#endif //STDCHAIN_PROCESS_CONSENSUS_VALIDATION_H
