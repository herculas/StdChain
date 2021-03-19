#include "type/blob/blob_256.h"

#include <vector>

Blob256::Blob256() = default;
Blob256::Blob256(uint8_t v) : BaseBlob<256>(v) {}
Blob256::Blob256(const std::vector<unsigned char> &vch) : BaseBlob(vch) {}
