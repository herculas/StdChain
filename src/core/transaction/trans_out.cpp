#include "core/transaction/trans_out.h"

TxOut::TxOut() : value(-1) {
    this->scriptPubKey.clear();
}

TxOut::TxOut(const Amount &value, Script scriptPukKey) {
    this->value = value;
    this->scriptPubKey = scriptPukKey;
}

bool TxOut::isNull() const {
    return this->value == -1;
}

std::string TxOut::toString() const {
    // TODO
    return std::string();
}

bool operator==(const TxOut &a, const TxOut &b) {
    return a.value == b.value && a.scriptPubKey == b.scriptPubKey;
}

bool operator!=(const TxOut &a, const TxOut &b) {
    return !(a == b);
}
