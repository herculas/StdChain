#ifndef STDCHAIN_TYPE_HASH_SHA256_H
#define STDCHAIN_TYPE_HASH_SHA256_H

#include <cstdint>
#include <cstdlib>

class SHA256 {

private:
    uint32_t s[8];
    uint64_t bytes;
    unsigned char buf[64];

public:
    static const size_t OUTPUT_SIZE = 32;

public:
    SHA256();
    SHA256 &write(const unsigned char *data, size_t len);
    void finalize(unsigned char hash[OUTPUT_SIZE]);
    SHA256 &reset();

};


#endif //STDCHAIN_TYPE_HASH_SHA256_H
