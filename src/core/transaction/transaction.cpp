#include "core/transaction/transaction.h"

#include <sstream>
#include <stdexcept>
#include <string>
#include "boost/format.hpp"
#include "config/amount.h"

Transaction::Transaction(const MutableTransaction &mTx) : version(mTx.version), lockTime(mTx.lockTime), vin(mTx.vin),
                                                          vout(mTx.vout), hash(this->computeHash()),
                                                          witnessHash(this->computeWitnessHash()) {}

Transaction::Transaction(MutableTransaction &&mTx) : version(mTx.version), lockTime(mTx.lockTime), vin(mTx.vin),
                                                     vout(mTx.vout), hash(this->computeHash()),
                                                     witnessHash(this->computeWitnessHash()) {}

bool Transaction::isNull() const {
    return this->vin.empty() && this->vout.empty();
}

const Blob256 &Transaction::getHash() const {
    return this->hash;
}

const Blob256 &Transaction::getWitnessHash() const {
    return this->witnessHash;
}

unsigned int Transaction::getTotalSize() const {
    // TODO: get serialize size
    return 0;
}

bool Transaction::isCoinbase() const {
    return this->vin.size() == 1 && this->vin[0].prevOut.isNull();
}

bool Transaction::hasWitness() const {
    for (const auto &in : this->vin) { // NOLINT(readability-use-anyofallof)
        if (!in.scriptWitness.isNull())
            return true;
    }
    return false;
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
    for (const auto &in : this->vin) stream << " " << in.toString() << "\n";
    for (const auto &in : this->vin) stream << " " << in.scriptWitness.toString() << "\n";
    for (const auto &out : this->vout) stream << " " << out.toString() << "\n";
    return stream.str();
}

Blob256 Transaction::computeHash() const {
    // TODO
    return Blob256();
}

Blob256 Transaction::computeWitnessHash() const {
    // TODO
    return Blob256();
}

bool operator==(const Transaction &a, const Transaction &b) {
    return a.hash == b.hash;
}

bool operator!=(const Transaction &a, const Transaction &b) {
    return a.hash != b.hash;
}
