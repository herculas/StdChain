#ifndef STDCHAIN_CORE_TRANSACTION_IN_H
#define STDCHAIN_CORE_TRANSACTION_IN_H

#include "core/transaction/trans_out_point.h"

class TxIn {

public:
    static const uint32_t SEQUENCE_FINAL = 0xffffffff;
    static const uint32_t SEQUENCE_LOCKTIME_DISABLE_FLAG = (1U << 31);
    static const uint32_t SEQUENCE_LOCKTIME_TYPE_FLAG = (1 << 22);
    static const uint32_t SEQUENCE_LOCKTIME_MASK = 0x0000ffff;
    static const uint32_t SEQUENCE_LOCKTIME_GRANULARITY = 9;

public:
    OutPoint preVout;
    uint32_t sequence;
    // TODO: Script: scriptSig
    // TODO: ScriptWitness: scriptWitness

public:
    TxIn();
};


#endif //STDCHAIN_CORE_TRANSACTION_IN_H
