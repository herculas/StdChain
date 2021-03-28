#ifndef STDCHAIN_UTIL_HASH_HASHER_H
#define STDCHAIN_UTIL_HASH_HASHER_H

#include "core/transaction/trans_out_point.h"

class SaltedTxOutpointHasher {

private:
    const uint64_t k0;
    const uint64_t k1;

public:
    SaltedTxOutpointHasher();
    size_t operator()(const TxOutPoint &id) const noexcept;

};

#endif //STDCHAIN_UTIL_HASH_HASHER_H
