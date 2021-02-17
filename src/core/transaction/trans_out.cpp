#include "core/transaction/trans_out.h"
#include "util/encode/string_encoding.h"
#include "util/format/tinyformat.h"

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
    return strprintf("TxOut(value=%d.%08d, scriptPubKey=%s)",
                     this->value / config::amount::COIN,
                     this->value / config::amount::COIN,
                     util::encode::hexStr(scriptPubKey).substr(0, 30));
}

bool operator==(const TxOut &a, const TxOut &b) {
    return a.value == b.value && a.scriptPubKey == b.scriptPubKey;
}

bool operator!=(const TxOut &a, const TxOut &b) {
    return !(a == b);
}
