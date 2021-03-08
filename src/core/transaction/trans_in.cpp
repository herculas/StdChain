#include "core/transaction/trans_in.h"
#include "util/encode/string_encoding.h"
#include "util/format/tinyformat.h"


TxIn::TxIn(): sequence(TxIn::SEQUENCE_FINAL) {}

TxIn::TxIn(OutPoint prevOut, Script scriptSig, uint32_t sequence) : prevOut(prevOut), scriptSig(scriptSig),
                                                                    sequence(sequence) {}

TxIn::TxIn(Blob256 hashPrevTx, uint32_t out, Script scriptSig, uint32_t sequence) : prevOut(OutPoint(hashPrevTx, out)),
                                                                                    scriptSig(scriptSig),
                                                                                    sequence(sequence) {}

std::string TxIn::toString() const {
    std::string str;
    str += "TxIn(" + this->prevOut.toString();
    if (this->prevOut.isNull())
        str += strprintf(", coinbase %s", util::encode::hexStr(this->scriptSig));
    else
        str += strprintf(", scriptSig=%s", util::encode::hexStr(this->scriptSig).substr(0, 24));
    if (this->sequence != TxIn::SEQUENCE_FINAL)
        str += strprintf(", sequence=%u", this->sequence);
    str += ")";
    return str;
}

bool operator==(const TxIn &a, const TxIn &b) {
    return a.prevOut == b.prevOut && a.scriptSig == b.scriptSig && a.sequence == b.sequence;
}

bool operator!=(const TxIn &a, const TxIn &b) {
    return !(a == b);
}
