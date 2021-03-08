#ifndef STDCHAIN_UTIL_HASH_H
#define STDCHAIN_UTIL_HASH_H

#include <vector>
#include "openssl/sha.h"
#include "type/blob/blob_256.h"

inline Blob256 sha256(const std::string &str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX context;
    SHA256_Init(&context);
    SHA256_Update(&context, str.c_str(), str.size());
    SHA256_Final(hash, &context);
    std::vector<unsigned char> vec(hash, hash + sizeof(hash) / sizeof(unsigned char));
    return Blob256{vec};
}

#endif //STDCHAIN_UTIL_HASH_H
