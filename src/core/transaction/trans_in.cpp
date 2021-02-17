#include "core/transaction/trans_in.h"

TxIn::TxIn(OutPoint prevOut, Script scriptSig, uint32_t sequence) : prevOut(prevOut), scriptSig(scriptSig),
                                                                    sequence(sequence) {}

TxIn::TxIn(Blob256 hashPrevTx, uint32_t out, Script scriptSig, uint32_t sequence) : prevOut(OutPoint(hashPrevTx, out)),
                                                                                    scriptSig(scriptSig),
                                                                                    sequence(sequence) {}

std::string TxIn::toString() const {
    return std::string();
}

bool operator==(const TxIn &a, const TxIn &b) {
    return a.prevOut == b.prevOut && a.scriptSig == b.scriptSig && a.sequence == b.sequence;
}

bool operator!=(const TxIn &a, const TxIn &b) {
    return !(a == b);
}
