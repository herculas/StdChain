#include "core/transaction/trans_out.h"

#include <sstream>
#include <utility>
#include "boost/format.hpp"

#include "config/amount.h"
#include "util/encode/string_encoding.h"

TxOut::TxOut() : value(-1) {
    this->scriptPubKey.clear();
}

TxOut::TxOut(const Amount &value, Script scriptPubKey) {
    this->value = value;
    this->scriptPubKey = std::move(scriptPubKey);
}

void TxOut::setNull() {
    this->value = -1;
    this->scriptPubKey.clear();
}

bool TxOut::isNull() const {
    return this->value == -1;
}

std::string TxOut::toString() const {
    std::stringstream stream;
    stream << boost::format("TxOut(value=%d.%08d, scriptPubKey=%s)")
              % (this->value / config::amount::COIN)
              % (this->value % config::amount::COIN)
              % util::encode::hexStr(scriptPubKey).substr(0, 30);
    return stream.str();
}

bool operator==(const TxOut &a, const TxOut &b) {
    return a.value == b.value && a.scriptPubKey == b.scriptPubKey;
}

bool operator!=(const TxOut &a, const TxOut &b) {
    return !(a == b);
}
