#ifndef STDCHAIN_CORE_COIN_VIEW_BACKED_H
#define STDCHAIN_CORE_COIN_VIEW_BACKED_H

#include <vector>
#include "core/coin/coin.h"
#include "core/coin/coin_cache_entry.h"
#include "core/coin/coin_view.h"
#include "core/coin/coin_view_cursor.h"
#include "core/transaction/trans_out_point.h"
#include "type/blob/blob_256.h"

class CoinViewBacked : public CoinView {

protected:
    CoinView *base;

public:
    explicit CoinViewBacked(CoinView *coinView);

    bool getCoin(const TxOutPoint &outPoint, Coin &coin) const override;
    [[nodiscard]] bool haveCoin(const TxOutPoint &outPoint) const override;
    [[nodiscard]] Blob256 getBestBlock() const override;
    [[nodiscard]] std::vector<Blob256> getHeadBlocks() const override;
    bool batchWrite(CoinMap &coinMap, const Blob256 &hashBlock) override;
    [[nodiscard]] CoinViewCursor *cursor() const override;
    [[nodiscard]] size_t estimateSize() const override;

    void setBackend(CoinView &coinView);

};


#endif //STDCHAIN_CORE_COIN_VIEW_BACKED_H
