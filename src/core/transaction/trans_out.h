#ifndef STDCHAIN_CORE_TRANSACTION_OUT_H
#define STDCHAIN_CORE_TRANSACTION_OUT_H

#include <string>
#include "config/amount.h"
#include "core/script/script.h"
#include "util/serialize/serialize.h"

class TxOut {

public:
    Amount value;
    Script scriptPubKey;

public:
    TxOut();
    TxOut(const Amount &value, Script scriptPukKey);

    [[nodiscard]] bool isNull() const;
    [[nodiscard]] std::string toString() const;

    template<typename Stream>
    void serialize(Stream &stream) const;

    friend bool operator==(const TxOut &a, const TxOut &b);
    friend bool operator!=(const TxOut &a, const TxOut &b);

};

template<typename Stream>
void TxOut::serialize(Stream &stream) const {
    static_assert(std::is_same<const TxOut&, decltype(*this)>::value, "Serialize type mismatch");
    util::serialize::serializeMany(stream,
                                   this->value,
                                   this->scriptPubKey);
}

#endif //STDCHAIN_CORE_TRANSACTION_OUT_H
