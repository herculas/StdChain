#include "core/transaction/trans_out_point.h"

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
    // TODO
    return this->hash.toString();
}
