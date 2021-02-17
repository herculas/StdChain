#ifndef STDCHAIN_CORE_TRANSACTION_OUT_H
#define STDCHAIN_CORE_TRANSACTION_OUT_H

#include <string>
#include "config/amount.h"
#include "core/script/script.h"

class TxOut {

public:
    Amount value;
    Script scriptPubKey;

public:
    TxOut();
    TxOut(const Amount &value, Script scriptPukKey);

    [[nodiscard]] bool isNull() const;
    [[nodiscard]] std::string toString() const;

    // TODO: serialize

    friend bool operator==(const TxOut &a, const TxOut &b);
    friend bool operator!=(const TxOut &a, const TxOut &b);

};

#endif //STDCHAIN_CORE_TRANSACTION_OUT_H
