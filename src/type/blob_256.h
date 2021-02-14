#ifndef STDCHAIN_TYPE_BLOB_256_H
#define STDCHAIN_TYPE_BLOB_256_H

#include "type/base_blob.h"

/**
 * 256-bit opaque blob.
 */
class Blob256 : public BaseBlob<256> {

public:
    Blob256();
    explicit Blob256(uint8_t v);

    unsigned char *begin();
    unsigned char *end();

    template<typename Stream>
    void Serialize(Stream &stream) const;

    template<typename Stream>
    void Unserialize(Stream &stream);
};

template<typename Stream>
void Blob256::Serialize(Stream &stream) const {
    stream.write((char *) this->data, sizeof(this->data));
}

template<typename Stream>
void Blob256::Unserialize(Stream &stream) {
    stream.read((char *) this->data, sizeof(this->data));
}

#endif //STDCHAIN_TYPE_BLOB_256_H
