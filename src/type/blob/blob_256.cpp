#include "blob_256.h"

Blob256::Blob256() = default;

Blob256::Blob256(uint8_t v) : BaseBlob<256>(v) {}

unsigned char *Blob256::begin() {
    return &this->data[0];
}

unsigned char *Blob256::end() {
    return &this->data[WIDTH];
}
