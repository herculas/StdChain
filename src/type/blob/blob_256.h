#ifndef STDCHAIN_TYPE_BLOB_256_H
#define STDCHAIN_TYPE_BLOB_256_H

#include <vector>
#include "type/blob/base_blob.h"

class Blob256 : public BaseBlob<256> {

public:
    Blob256();
    explicit Blob256(uint8_t v);
    explicit Blob256(const std::vector<unsigned char>&vch): BaseBlob<256>(vch) {}
};

#endif //STDCHAIN_TYPE_BLOB_256_H
