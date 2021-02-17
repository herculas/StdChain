#include "core/transaction/transaction.h"

#include <stdexcept>
#include <string>
#include "config/version.h"
#include "util/format/tinyformat.h"
#include "util/serialize/config.h"
#include "util/serialize/hash.h"
#include "util/serialize/transaction.h"

Transaction::Transaction(const MutableTransaction &mTx) : version(mTx.version), lockTime(mTx.lockTime), vin(mTx.vin),
                                                          vout(mTx.vout), hash{this->computeHash()},
                                                          witnessHash{this->computeWitnessHash()} {
}

Transaction::Transaction(MutableTransaction &&mTx) : version(mTx.version), lockTime(mTx.lockTime), vin(mTx.vin),
                                                     vout(mTx.vout), hash{this->computeHash()},
                                                     witnessHash(this->computeWitnessHash()) {
}

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

std::string Transaction::toString() const {
    std::string str;
    str += strprintf("Transaction(hash=%s, ver=%d, vin.size=%u, vout.size=%u, locktime=%u)\n",
                     this->getHash().toString().substr(0, 10),
                     this->version,
                     this->vin.size(),
                     this->vout.size(),
                     this->lockTime);
    for (const auto &in : this->vin) str += "  " + in.toString() + "\n";
    for (const auto &in : this->vin) str += "  " + in.scriptWitness.toString() + "\n";
    for (const auto &out : this->vout) str += "  " + out.toString() + "\n";
    return str;
}

Amount Transaction::getValueOut() const {
    Amount valueOut = 0;
    for (const auto &out : vout) {
        if (!config::amount::moneyRange(out.value) || !config::amount::moneyRange(valueOut + out.value))
            throw std::runtime_error(std::string(__func__) + ": value out of range.");
        valueOut += out.value;
    }
    assert(config::amount::moneyRange(valueOut));
    return valueOut;
}

bool Transaction::hasWitness() const {
    for (const auto &in : this->vin) { // NOLINT(readability-use-anyofallof)
        if (!in.scriptWitness.isNull())
            return true;
    }
    return false;
}

Blob256 Transaction::computeHash() const {
    return util::serialize::serializeHash(*this, util::serialize::SER_GETHASH,
                                          config::version::SERIALIZE_TRANSACTION_NO_WITNESS);
}

Blob256 Transaction::computeWitnessHash() const {
    if (!this->hasWitness())
        return this->hash;
    return util::serialize::serializeHash(*this, util::serialize::SER_GETHASH, 0);
}

bool operator==(const Transaction &a, const Transaction &b) {
    return a.hash == b.hash;
}

bool operator!=(const Transaction &a, const Transaction &b) {
    return a.hash != b.hash;
}

template<typename Stream>
void Transaction::serialize(Stream &stream) const {
    util::serialize::serializeTransaction(*this, stream);
}
