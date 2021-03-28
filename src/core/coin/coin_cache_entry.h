#ifndef STDCHAIN_CORE_COIN_CACHE_ENTRY_H
#define STDCHAIN_CORE_COIN_CACHE_ENTRY_H

#include <unordered_map>
#include "core/coin/coin.h"
#include "core/transaction/trans_out_point.h"
#include "util/hash/hasher.h"

class CoinCacheEntry {

public:
    enum Flags {
        DIRTY = (1 << 0),
        FRESH = (1 << 1),
    };

public:
    Coin coin;
    unsigned char flag;

public:
    CoinCacheEntry();
    explicit CoinCacheEntry(Coin &&coin);
    CoinCacheEntry(Coin && coin, unsigned char flag);

};

typedef std::unordered_map<TxOutPoint, CoinCacheEntry, SaltedTxOutpointHasher> CoinMap;

#endif //STDCHAIN_CORE_COIN_CACHE_ENTRY_H
