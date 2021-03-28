#ifndef STDCHAIN_CORE_COIN_H
#define STDCHAIN_CORE_COIN_H

#include "core/transaction/trans_out.h"

// A UTxO entry
class Coin {

public:
    TxOut out;
    bool coinbase;
    uint32_t height;

public:
    Coin();
    Coin(TxOut &&out, uint32_t height, bool coinbase);
    Coin(TxOut out, uint32_t height, bool coinbase);

    void clear();
    [[nodiscard]] bool isCoinbase() const;
    [[nodiscard]] bool isSpent() const;
    [[nodiscard]] size_t dynamicMemoryUsage() const;

};

#endif //STDCHAIN_CORE_COIN_H
