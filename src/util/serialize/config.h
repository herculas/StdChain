#ifndef STDCHAIN_UTIL_SERIALIZE_CONFIG_H
#define STDCHAIN_UTIL_SERIALIZE_CONFIG_H

namespace util::serialize {
    enum {
        SER_NETWORK = (1 << 0),
        SER_DISK = (1 << 1),
        SER_GETHASH = (1 << 2),
    };
}

#endif //STDCHAIN_UTIL_SERIALIZE_CONFIG_H
