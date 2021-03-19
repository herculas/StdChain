#include "core/transaction/transaction.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <string>
#include "boost/archive/text_oarchive.hpp"
#include "boost/format.hpp"
#include "config/amount.h"
#include "config/transaction.h"
#include "util/hash/sha256.h"

Transaction::Transaction(const MutableTransaction &mTx) : version(mTx.version), lockTime(mTx.lockTime), vin(mTx.vin),
                                                          vout(mTx.vout), hash(this->computeHash()),
                                                          witnessHash(this->computeWitnessHash()) {}

Transaction::Transaction(MutableTransaction &&mTx) : version(mTx.version), lockTime(mTx.lockTime), vin(mTx.vin),
                                                     vout(mTx.vout), hash(this->computeHash()),
                                                     witnessHash(this->computeWitnessHash()) {}

Transaction::Transaction() : version(0), lockTime(0), vin(), vout(), hash(), witnessHash() {}

bool Transaction::isNull() const {
    return this->vin.empty() && this->vout.empty();
}

const Blob256 &Transaction::getHash() const {
    return this->hash;
}

const Blob256 &Transaction::getWitnessHash() const {
    return this->witnessHash;
}

uint32_t Transaction::getTotalSize() const {
    int32_t totalSize = 0;
    totalSize += sizeof(this->version) + sizeof(this->lockTime);
    for (const auto &in : this->vin) totalSize += sizeof(in);
    for (const auto &out: this->vout) totalSize += sizeof(out);
    return  totalSize;
}

bool Transaction::isCoinbase() const {
    return this->vin.size() == 1 && this->vin[0].prevOut.isNull();
}

bool Transaction::hasWitness() const {
    return std::any_of(this->vin.begin(), this->vin.end(), [](const TxIn &in){
        return !in.scriptWitness.isNull();
    });
}

Amount Transaction::getValueOut() const {
    Amount valueOut = 0;
    for (const auto &out: vout) {
        if (!config::amount::moneyRange(out.value) || !config::amount::moneyRange(valueOut + out.value))
            throw std::runtime_error(std::string(__func__) + ": value out of range.");
        valueOut += out.value;
    }
    assert(config::amount::moneyRange(valueOut));
    return valueOut;
}

std::string Transaction::toString() const {
    std::stringstream stream;
    stream << boost::format("Transaction(hash=%s, ver=%d, vin.size=%u, vout.size=%u, locktime=%u)\n")
              % this->getHash().toString().substr(0, 10)
              % this->version
              % this->vin.size()
              % this->vout.size()
              % this->lockTime;
    for (const auto &in : this->vin) stream << "\t\t" << in.toString() << "\n";
    for (const auto &out : this->vout) stream << "\t\t" << out.toString() << "\n";
    return stream.str();
}

Blob256 Transaction::computeHash() const {
    std::stringstream stream;
    stream << this->version << this->lockTime << config::transaction::SERIALIZE_TRANSACTION_NO_WITNESS;
    boost::archive::text_oarchive archive(stream);
    for (const auto &in : this->vin) archive << in;
    for (const auto &out : this->vout) archive << out;
    return util::hash::sha256(stream.str());
}

Blob256 Transaction::computeWitnessHash() const {
    if (!this->hasWitness()) return this->computeHash();
    std::stringstream stream;
    stream << this->version << this->lockTime << 0;
    boost::archive::text_oarchive archive(stream);
    for (const auto &in : this->vin) archive << in;
    for (const auto &out : this->vout) archive << out;
    return util::hash::sha256(stream.str());
}

bool operator==(const Transaction &a, const Transaction &b) {
    return a.hash == b.hash;
}

bool operator!=(const Transaction &a, const Transaction &b) {
    return a.hash != b.hash;
}
