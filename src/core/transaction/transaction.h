#ifndef STDCHAIN_CORE_TRANSACTION_H
#define STDCHAIN_CORE_TRANSACTION_H

#include <cstdint>
#include <string>
#include <vector>
#include "core/transaction/mutable_trans.h"
#include "core/transaction/trans_in.h"
#include "core/transaction/trans_out.h"
#include "type/blob/blob_256.h"

class Transaction {

public:
    static const int32_t CURRENT_VERSION = 2;
    const int32_t version;
    const uint32_t lockTime;
    const std::vector<TxIn> vin;
    const std::vector<TxOut> vout;

private:
    const Blob256 hash;
    const Blob256 witnessHash;

public:
    explicit Transaction(const MutableTransaction &mTx);
    explicit Transaction(MutableTransaction &&mTx);

    template<typename Stream>
    inline void serialize(Stream &stream) const;

    [[nodiscard]] bool isNull() const;
    [[nodiscard]] const Blob256 &getHash() const;
    [[nodiscard]] const Blob256 &getWitnessHash() const;

    [[nodiscard]] unsigned int getTotalSize() const;
    [[nodiscard]] bool isCoinbase() const;
    [[nodiscard]] bool hasWitness() const;
    [[nodiscard]] std::string toString() const;

private:
    [[nodiscard]] Blob256 computeHash() const;
    [[nodiscard]] Blob256 computeWitnessHash() const;

};


#endif //STDCHAIN_CORE_TRANSACTION_H
