#include "core/transaction/trans_id_generic.h"

#include <tuple>

TxIDGeneric::TxIDGeneric(bool isWitnessTxID, const Blob256 &hash): isWitnessTxID(isWitnessTxID), hash(hash) {}

bool TxIDGeneric::isWitnessTransID() const {
    return this->isWitnessTxID;
}

const Blob256 &TxIDGeneric::getHash() const {
    return this->hash;
}

bool operator==(const TxIDGeneric &a, const TxIDGeneric &b) {
    return a.isWitnessTxID == b.isWitnessTxID && a.hash == b.hash;
}

bool operator<(const TxIDGeneric &a, const TxIDGeneric &b) {
    return std::tie(a.isWitnessTxID, a.hash) < std::tie(b.isWitnessTxID, b.hash);
}
