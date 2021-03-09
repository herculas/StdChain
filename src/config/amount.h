#ifndef STDCHAIN_AMOUNT_H
#define STDCHAIN_AMOUNT_H

#include "type/basic/amount.h"

namespace config::amount {
    static const Amount COIN = 100000000;
    static const Amount MAX_MONEY = 21000000 * COIN;

    inline bool moneyRange(const Amount &value) {
        return value >= 0 && value <= MAX_MONEY;
    }
}

#endif //STDCHAIN_AMOUNT_H
