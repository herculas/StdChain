#ifndef STDCHAIN_CONFIG_AMOUNT_H
#define STDCHAIN_CONFIG_AMOUNT_H

typedef int64_t Amount;

namespace config::amount {

    static const Amount COIN = 100000000;
    static const Amount MAX_MONEY = 21000000 * COIN;

    inline bool moneyRange(const Amount &value) {
        return value >= 0 && value <= MAX_MONEY;
    }
}

#endif //STDCHAIN_CONFIG_AMOUNT_H
