#include "core/transaction/trans_out_point.h"

#include <sstream>
#include "boost/format.hpp"

TxOutPoint::TxOutPoint() : n(TxOutPoint::NULL_INDEX) {}
TxOutPoint::TxOutPoint(uint32_t n, Blob256 &hash): n(n), hash(hash) {}

void TxOutPoint::setNull() {
    this->n = TxOutPoint::NULL_INDEX;
    this->hash.setNull();
}

bool TxOutPoint::isNull() const {
    return this->n == TxOutPoint::NULL_INDEX && this->hash.isNull();
}

std::string TxOutPoint::toString() const {
    std::stringstream stream;
    stream << boost::format("TxOutPoint(%u, %s)")
              % this->n
              % this->hash.toString().substr(0, 10);
    return stream.str();
}

bool operator<(const TxOutPoint &a, const TxOutPoint &b) {
    uint32_t cmp = a.hash.compare(b.hash);
    return cmp < 0 || (cmp == 0 && a.n < b.n);
}

bool operator==(const TxOutPoint &a, const TxOutPoint &b) {
    return a.hash == b.hash && a.n == b.n;
}

bool operator!=(const TxOutPoint &a, const TxOutPoint &b) {
    return !(a == b);
}
