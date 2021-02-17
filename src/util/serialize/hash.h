#ifndef STDCHAIN_UTIL_SERIALIZE_HASH_H
#define STDCHAIN_UTIL_SERIALIZE_HASH_H

#include "config/version.h"
#include "type/hash/hash_writer.h"
#include "util/serialize/config.h"

namespace util::serialize {
    template<typename T>
    Blob256
    serializeHash(const T &obj, int type = util::serialize::SER_GETHASH, int version = config::version::PROTOCOL_VERSION) {
        HashWriter ss(type, version);
        ss << obj;
        return ss.getHash();
    }
}

#endif //STDCHAIN_UTIL_SERIALIZE_HASH_H
