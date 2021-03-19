#ifndef STDCHAIN_CORE_TRANSACTION_H
#define STDCHAIN_CORE_TRANSACTION_H

#include <memory>
#include <string>
#include <vector>
#include "boost/serialization/vector.hpp"
#include "config/amount.h"
#include "core/transaction/mutable_trans.h"
#include "core/transaction/trans_in.h"
#include "core/transaction/trans_out.h"
#include "type/blob/blob_256.h"

class Transaction {

public:
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

    [[nodiscard]] bool isNull() const;
    [[nodiscard]] const Blob256 &getHash() const;
    [[nodiscard]] const Blob256 &getWitnessHash() const;

    [[nodiscard]] uint32_t getTotalSize() const;
    [[nodiscard]] bool isCoinbase() const;
    [[nodiscard]] bool hasWitness() const;
    [[nodiscard]] Amount getValueOut() const;
    [[nodiscard]] std::string toString() const;

private:
    [[nodiscard]] Blob256 computeHash() const;
    [[nodiscard]] Blob256 computeWitnessHash() const;

public:
    friend bool operator==(const Transaction &a, const Transaction &b);
    friend bool operator!=(const Transaction &a, const Transaction &b);

private:
    Transaction();
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &archive, uint32_t ver);

};

template<typename Archive>
void Transaction::serialize(Archive &archive, uint32_t ver) {
    archive & const_cast<int32_t &>(this->version);
    archive & const_cast<uint32_t &>(this->lockTime);
    archive & const_cast<std::vector<TxIn> &>(this->vin);
    archive & const_cast<std::vector<TxOut> &>(this->vout);
    archive & const_cast<Blob256 &>(this->hash);
    archive & const_cast<Blob256 &>(this->witnessHash);
}

#endif //STDCHAIN_CORE_TRANSACTION_H
