#ifndef STDCHAIN_UTIL_HASH_SHA256_H
#define STDCHAIN_UTIL_HASH_SHA256_H

#include <vector>
#include "openssl/sha.h"
#include "type/blob/blob_256.h"

namespace util::hash {
    inline Blob256 sha256(const std::string &str) {
        unsigned char hash[SHA256_DIGEST_LENGTH];

        SHA256_CTX context;
        SHA256_Init(&context);
        SHA256_Update(&context, str.c_str(), str.size());
        SHA256_Final(hash, &context);

        return Blob256{std::vector<unsigned char>{hash, hash + sizeof(hash) / sizeof(unsigned char)}};
    }
}

#endif //STDCHAIN_UTIL_HASH_SHA256_H
