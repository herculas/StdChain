#ifndef STDCHAIN_CORE_COIN_VIEW_CACHE_H
#define STDCHAIN_CORE_COIN_VIEW_CACHE_H

#include "core/coin/coin.h"
#include "core/coin/coin_cache_entry.h"
#include "core/coin/coin_view_backed.h"
#include "core/coin/coin_view_cursor.h"
#include "core/transaction/transaction.h"
#include "type/blob/blob_256.h"

class CoinViewCache : public CoinViewBacked {

protected:
    mutable Blob256 hashBlock;
    mutable CoinMap cacheCoins;
    mutable size_t cachedCoinsUsage;

public:
    explicit CoinViewCache(CoinView *base);
    CoinViewCache(const CoinViewCache &) = delete;

    bool getCoin(const TxOutPoint &outPoint, Coin &coin) const override;
    bool haveCoin(const TxOutPoint &outPoint) const override;
    Blob256 getBestBlock() const override;
    bool batchWrite(CoinMap &coinMap, const Blob256 &hashBlock) override;
    CoinViewCursor *cursor() const override;

    void setBestBlock(const Blob256 &hashBlock);
    bool haveCoinInCache(const TxOutPoint &outPoint) const;
    const Coin &accessCoin(const TxOutPoint &outPoint) const;
    void addCoin(const TxOutPoint &outPoint, Coin &&coin, bool possibleOverwrite);
    void emplaceCoinInternalDanger(TxOutPoint &&outPoint, Coin &&coin);
    bool spendCoin(const TxOutPoint &outPoint, Coin *moveTo = nullptr);
    bool flush();
    void unCache(const TxOutPoint &outPoint);
    uint32_t getCacheSize() const;
    size_t dynamicMemoryUsage() const;
    bool haveInputs(const Transaction &transaction) const;
    void reallocateCache();

private:
    CoinMap::iterator fetchCoin(const TxOutPoint &outPoint) const;

};


#endif //STDCHAIN_CORE_COIN_VIEW_CACHE_H
