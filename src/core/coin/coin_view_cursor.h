#ifndef STDCHAIN_CORE_COIN_VIEW_CURSOR_H
#define STDCHAIN_CORE_COIN_VIEW_CURSOR_H

#include "core/coin/coin.h"
#include "core/transaction/trans_out_point.h"
#include "type/blob/blob_256.h"

// Cursor for iterating over CoinView state.
class CoinViewCursor {

private:
    Blob256 hashBlock;

public:
    explicit CoinViewCursor(const Blob256 &hashBlock);
    virtual ~CoinViewCursor();

    virtual void next() = 0;
    virtual bool getKey(TxOutPoint &key) const = 0;
    virtual bool getValue(Coin &coin) const = 0;
    [[nodiscard]] virtual uint32_t getValueSize() const = 0;
    [[nodiscard]] virtual bool valid() const = 0;

    [[nodiscard]] const Blob256 &getBestBlock() const;
};


#endif //STDCHAIN_CORE_COIN_VIEW_CURSOR_H
