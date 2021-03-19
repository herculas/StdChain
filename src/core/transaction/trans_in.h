#ifndef STDCHAIN_CORE_TRANSACTION_INPUT_H
#define STDCHAIN_CORE_TRANSACTION_INPUT_H

#include <cstdint>
#include <string>

#include "config/transaction.h"
#include "core/script/script.h"
#include "core/script/script_witness.h"
#include "core/transaction/trans_out_point.h"

class TxIn {

public:
    TxOutPoint prevOut;
    uint32_t sequence;
    Script scriptSig;
    ScriptWitness scriptWitness;

public:
    explicit TxIn(TxOutPoint prevOut,
                  Script scriptSig = Script(),
                  uint32_t sequence = config::transaction::SEQUENCE_FINAL);
    TxIn(Blob256 hashPrevTx,
         uint32_t out,
         Script scriptSig = Script(),
         uint32_t sequence = config::transaction::SEQUENCE_FINAL);

    [[nodiscard]] std::string toString() const;

    friend bool operator==(const TxIn &a, const TxIn &b);
    friend bool operator!=(const TxIn &a, const TxIn &b);

private:
    TxIn();
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &archive, uint32_t version);
};

template<typename Archive>
void TxIn::serialize(Archive &archive, uint32_t version) {
    archive & this->prevOut;
    archive & this->sequence;
    archive & this->scriptSig;
    archive & this->scriptWitness;
}

#endif //STDCHAIN_CORE_TRANSACTION_INPUT_H
