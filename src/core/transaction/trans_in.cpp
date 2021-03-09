#include "core/transaction/trans_in.h"

#include <type_traits>

TxIn::TxIn(TxOutPoint prevOut, Script scriptSig, uint32_t sequence) : prevOut(prevOut), scriptSig(std::move(scriptSig)),
                                                                      sequence(sequence) {}

TxIn::TxIn(Blob256 hashPrevTx, uint32_t out, Script scriptSig, uint32_t sequence) : prevOut(TxOutPoint(out, hashPrevTx)),
                                                                                    scriptSig(std::move(scriptSig)),
                                                                                    sequence(sequence) {}

std::string TxIn::toString() const {
    // TODO
    return std::string();
}

bool operator==(const TxIn &a, const TxIn &b) {
    return a.prevOut == b.prevOut && a.scriptSig == b.scriptSig && a.sequence == b.sequence;
}

bool operator!=(const TxIn &a, const TxIn &b) {
    return !(a == b);
}
