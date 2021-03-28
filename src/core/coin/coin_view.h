#ifndef STDCHAIN_CORE_COIN_VIEW_H
#define STDCHAIN_CORE_COIN_VIEW_H

#include <vector>
#include "core/coin/coin.h"
#include "core/coin/coin_cache_entry.h"
#include "core/coin/coin_view_cursor.h"
#include "core/transaction/trans_out_point.h"
#include "type/blob/blob_256.h"

// Abstract view on the open TxOut dataset.
class CoinView {

public:
    virtual ~CoinView();

    virtual bool getCoin(const TxOutPoint &outPoint, Coin &coin) const;
    [[nodiscard]] virtual bool haveCoin(const TxOutPoint &outPoint) const;
    [[nodiscard]] virtual Blob256 getBestBlock() const;
    [[nodiscard]] virtual std::vector<Blob256> getHeadBlocks() const;
    virtual bool batchWrite(CoinMap &coinMap, const Blob256 &hashBlock);
    [[nodiscard]] virtual CoinViewCursor *cursor() const;
    [[nodiscard]] virtual size_t estimateSize() const;

};


#endif //STDCHAIN_CORE_COIN_VIEW_H
