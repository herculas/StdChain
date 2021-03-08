#ifndef STDCHAIN_UTIL_SERIALIZE_TRANSACTION_H
#define STDCHAIN_UTIL_SERIALIZE_TRANSACTION_H

#include <vector>
#include "config/version.h"
#include "core/transaction/trans_in.h"

namespace util::serialize {

    template<typename Stream, typename TxType>
    inline void serializeTransaction(const TxType &transaction, Stream &stream) {
        const bool allowWitness = !(stream.getVersion() & config::version::SERIALIZE_TRANSACTION_NO_WITNESS);
        stream << transaction.version;
        unsigned char flags = 0;
        if (allowWitness) {
            if (transaction.hasWitness()) {
                flags |= 1;
            }
        }
        if (flags) {
            std::vector<TxIn> vinDummy;
            stream << vinDummy;
            stream << flags;
        }
        stream << transaction.vin;
        stream << transaction.vout;
        if (flags & 1) {
            for (int i = 0; i < transaction.vin.size(); ++i) {
                stream << transaction.vin[i].scriptWitness.stack;
            }
        }
        stream << transaction.lockTime;
    }
}

#endif //STDCHAIN_UTIL_SERIALIZE_TRANSACTION_H
