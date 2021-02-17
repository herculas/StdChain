#ifndef STDCHAIN_CORE_TRANSACTION_IN_H
#define STDCHAIN_CORE_TRANSACTION_IN_H

#include "core/script/script.h"
#include "core/script/script_witness.h"
#include "core/transaction/trans_out_point.h"
#include "type/blob/blob_256.h"

class TxIn {

public:
    static const uint32_t SEQUENCE_FINAL = 0xffffffff;
    static const uint32_t SEQUENCE_LOCKTIME_DISABLE_FLAG = (1U << 31);
    static const uint32_t SEQUENCE_LOCKTIME_TYPE_FLAG = (1 << 22);
    static const uint32_t SEQUENCE_LOCKTIME_MASK = 0x0000ffff;
    static const uint32_t SEQUENCE_LOCKTIME_GRANULARITY = 9;

public:
    OutPoint prevOut;
    uint32_t sequence;
    Script scriptSig;
    ScriptWitness scriptWitness;

public:
    explicit TxIn(OutPoint prevOut, Script scriptSig = Script(), uint32_t sequence = TxIn::SEQUENCE_FINAL);
    TxIn(Blob256 hashPrevTx, uint32_t out, Script scriptSig = Script(), uint32_t sequence = TxIn::SEQUENCE_FINAL);

    [[nodiscard]] std::string toString() const;

    // TODO: serialize

    friend bool operator==(const TxIn &a, const TxIn &b);
    friend bool operator!=(const TxIn &a, const TxIn &b);

};


#endif //STDCHAIN_CORE_TRANSACTION_IN_H
