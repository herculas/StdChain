#include "core/transaction/trans_in.h"

#include <sstream>
#include <type_traits>
#include "util/encode/string_encoding.h"

TxIn::TxIn(TxOutPoint prevOut, Script scriptSig, uint32_t sequence) : prevOut(prevOut), scriptSig(std::move(scriptSig)),
                                                                      sequence(sequence) {}

TxIn::TxIn(Blob256 hashPrevTx, uint32_t out, Script scriptSig, uint32_t sequence) : prevOut(TxOutPoint(out, hashPrevTx)),
                                                                                    scriptSig(std::move(scriptSig)),
                                                                                    sequence(sequence) {}

TxIn::TxIn() : prevOut(), scriptSig(), sequence() {}

std::string TxIn::toString() const {
    std::stringstream stream;
    stream << "TxIn(" << this->prevOut.toString();
    if (this->prevOut.isNull())
        stream << ", coinbase " << util::encode::hexStr(scriptSig);
    else
        stream << ", scriptSig=" << util::encode::hexStr(scriptSig).substr(0, 24);
    if (this->sequence != TxIn::SEQUENCE_FINAL)
        stream << ", sequence=" << this->sequence;
    stream << ")";
    return stream.str();
}

bool operator==(const TxIn &a, const TxIn &b) {
    return a.prevOut == b.prevOut && a.scriptSig == b.scriptSig && a.sequence == b.sequence;
}

bool operator!=(const TxIn &a, const TxIn &b) {
    return !(a == b);
}
