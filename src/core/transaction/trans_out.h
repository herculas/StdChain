#ifndef STDCHAIN_CORE_TRANSACTION_OUTPUT_H
#define STDCHAIN_CORE_TRANSACTION_OUTPUT_H

#include <string>
#include "type/basic/amount.h"
#include "core/script/script.h"

class TxOut {

public:
    Amount value;
    Script scriptPubKey;

public:
    TxOut();
    TxOut(const Amount &value, Script scriptPubKey);

    [[nodiscard]] bool isNull() const;
    [[nodiscard]] std::string toString() const;

    friend bool operator==(const TxOut &a, const TxOut &b);
    friend bool operator!=(const TxOut &a, const TxOut &b);
};


#endif //STDCHAIN_CORE_TRANSACTION_OUTPUT_H
