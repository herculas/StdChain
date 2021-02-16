#ifndef STDCHAIN_TYPE_BLOB_256_H
#define STDCHAIN_TYPE_BLOB_256_H

#include "type/blob/base_blob.h"

class Blob256 : public BaseBlob<256> {

public:
    Blob256();
    explicit Blob256(uint8_t v);

    unsigned char *begin();
    unsigned char *end();

    template<typename Stream>
    void serialize(Stream &stream) const;

    template<typename Stream>
    void deserialize(Stream &stream);
};

template<typename Stream>
void Blob256::serialize(Stream &stream) const {
    stream.write((char *) this->data, sizeof(this->data));
}

template<typename Stream>
void Blob256::deserialize(Stream &stream) {
    stream.read((char *) this->data, sizeof(this->data));
}

#endif //STDCHAIN_TYPE_BLOB_256_H
