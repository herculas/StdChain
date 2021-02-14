#ifndef STDCHAIN_UTIL_HASH_HASH_WRITER_H
#define STDCHAIN_UTIL_HASH_HASH_WRITER_H

#include "config/version.h"
#include "type/blob_256.h"
#include "util/encode/serialize.h"
#include "util/hash/sha256.h"

class HashWriter {

private:
    SHA256 ctx;
    const int type;
    const int version;

public:
    HashWriter(int type, int version);
    [[nodiscard]] int getType() const;
    [[nodiscard]] int getVersion() const;
    void write(const char *pch, size_t size);
    Blob256 getHash();
    Blob256 getSHA256();
    uint64_t getCheapHash();

    template<typename T>
    HashWriter &operator<<(const T &obj);

};

template<typename T>
HashWriter &HashWriter::operator<<(const T &obj) {
    ::Serialize(*this, obj);
    return *this;
}

template<typename T>
Blob256 serializeHash(const T& obj, int type=SER_GETHASH, int version=PROTOCOL_VERSION) {
    HashWriter ss(type, version);
    ss << obj;
    return ss.getHash();
}

#endif //STDCHAIN_UTIL_HASH_HASH_WRITER_H
