#include "core/transaction/trans_out_point.h"
#include "util/format/tinyformat.h"

OutPoint::OutPoint(): n(OutPoint::NULL_INDEX) {}
OutPoint::OutPoint(const Blob256 &hash, uint32_t n):hash(hash), n(n) {}

void OutPoint::setNull() {
    this->hash.setNull();
    this->n = OutPoint::NULL_INDEX;
}

bool OutPoint::isNull() const {
    return this->hash.isNull() && this->n == OutPoint::NULL_INDEX;
}

std::string OutPoint::toString() const {
    return strprintf("OutPoint(%s, %u)", this->hash.toString().substr(0, 10), this->n);
}

bool operator<(const OutPoint &a, const OutPoint &b) {
    int cmp = a.hash.compare(b.hash);
    return cmp < 0 || (cmp == 0 && a.n < b.n);
}

bool operator==(const OutPoint &a, const OutPoint &b) {
    return a.hash == b.hash && a.n == b.n;
}

bool operator!=(const OutPoint &a, const OutPoint &b) {
    return !(a == b);
}
