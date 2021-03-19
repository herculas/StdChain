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

    void setNull();
    [[nodiscard]] bool isNull() const;
    [[nodiscard]] std::string toString() const;

    friend bool operator==(const TxOut &a, const TxOut &b);
    friend bool operator!=(const TxOut &a, const TxOut &b);

private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &archive, uint32_t version);

};

template<typename Archive>
void TxOut::serialize(Archive &archive, uint32_t version) {
    archive & this->value;
    archive & this->scriptPubKey;
}

#endif //STDCHAIN_CORE_TRANSACTION_OUTPUT_H
