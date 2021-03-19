#include "core/transaction/mutable_trans.h"

#include <algorithm>
#include <sstream>
#include "config/transaction.h"
#include "core/transaction/transaction.h"
#include "util/hash/sha256.h"

MutableTransaction::MutableTransaction() : version(config::transaction::CURRENT_VERSION), lockTime(0) {}

MutableTransaction::MutableTransaction(const Transaction &tx) : vin(tx.vin),
                                                                vout(tx.vout),
                                                                version(tx.version),
                                                                lockTime(tx.lockTime) {}

Blob256 MutableTransaction::getHash() const {
    std::stringstream stream;
    stream << this->version << this->lockTime << config::transaction::SERIALIZE_TRANSACTION_NO_WITNESS;
    boost::archive::text_oarchive archive(stream);
    for (const auto &in : this->vin) archive << in;
    for (const auto &out : this->vout) archive << out;
    return util::hash::sha256(stream.str());
}

bool MutableTransaction::hasWitness() const {
    return std::any_of(this->vin.begin(), this->vin.end(), [](const TxIn &in) {
        return !in.scriptWitness.isNull();
    });
}
