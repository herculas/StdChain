#ifndef STDCHAIN_CORE_TRANSACTION_INPUT_H
#define STDCHAIN_CORE_TRANSACTION_INPUT_H

#include <cstdint>
#include <string>

#include "core/script/script.h"
#include "core/script/script_witness.h"
#include "core/transaction/trans_out_point.h"

class TxIn {

public:
    static const uint32_t SEQUENCE_FINAL = 0xffffffff;
    static const uint32_t SEQUENCE_LOCKTIME_DISABLE_FLAG = (1U << 31);
    static const uint32_t SEQUENCE_LOCKTIME_TYPE_FLAG = (1 << 22);
    static const uint32_t SEQUENCE_LOCKTIME_MASK = 0x0000ffff;
    static const uint32_t SEQUENCE_LOCKTIME_GRANULARITY = 9;

public:
    TxOutPoint prevOut;
    uint32_t sequence;
    Script scriptSig;
    ScriptWitness scriptWitness;

public:
    explicit TxIn(TxOutPoint prevOut, Script scriptSig = Script(), uint32_t sequence = TxIn::SEQUENCE_FINAL);
    TxIn(Blob256 hashPrevTx, uint32_t out, Script scriptSig = Script(), uint32_t sequence = TxIn::SEQUENCE_FINAL);

    [[nodiscard]] std::string toString() const;

    friend bool operator==(const TxIn &a, const TxIn &b);
    friend bool operator!=(const TxIn &a, const TxIn &b);

private:
    TxIn();
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &archive, unsigned int archiveVersion);
};

template<typename Archive>
void TxIn::serialize(Archive &archive, unsigned int archiveVersion) {
    archive & this->prevOut;
    archive & this->sequence;
    archive & this->scriptSig;
    archive & this->scriptWitness;
}

#endif //STDCHAIN_CORE_TRANSACTION_INPUT_H
