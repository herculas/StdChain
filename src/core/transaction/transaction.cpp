#include "core/transaction/transaction.h"

#include "config/version.h"
#include "util/serialize/hash.h"
#include "util/serialize/config.h"

Transaction::Transaction(const MutableTransaction &mTx) : version(mTx.version), lockTime(mTx.lockTime), vin(mTx.vin),
                                                          vout(mTx.vout), hash{this->computeHash()},
                                                          witnessHash{this->computeWitnessHash()} {
}

Transaction::Transaction(MutableTransaction &&mTx) : version(mTx.version), lockTime(mTx.lockTime), vin(mTx.vin),
                                                     vout(mTx.vout), hash{this->computeHash()},
                                                     witnessHash(this->computeWitnessHash()) {
}

template<typename Stream>
void Transaction::serialize(Stream &stream) const {

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

Blob256 Transaction::computeHash() const {
    return util::serialize::serializeHash(*this, util::serialize::SER_GETHASH,
                                          config::SERIALIZE_TRANSACTION_NO_WITNESS);
}

Blob256 Transaction::computeWitnessHash() const {
    if (!this->hasWitness())
        return this->hash;
    return util::serialize::serializeHash(*this, util::serialize::SER_GETHASH, 0);
}

unsigned int Transaction::getTotalSize() const {
    return 0;
}

bool Transaction::isCoinbase() const {
    // TODO: return this->vin.size() == 1 && this->vin[0];
    return false;
}

std::string Transaction::toString() const {
    // TODO
    return std::string();
}

bool Transaction::hasWitness() const {
    // TODO
    return false;
}

