#include "type/arith/uint_256.h"
#include "util/encode/common.h"

Uint256::Uint256() = default;
Uint256::Uint256(const BaseUint<256> &base) : BaseUint<256>(base) {}
Uint256::Uint256(uint64_t base) : BaseUint<256>(base) {}
Uint256::Uint256(const std::string &str) : BaseUint<256>(str) {}

Uint256 &Uint256::setCompact(uint32_t compact, bool *negative, bool *overflow) {
    int32_t size = compact >> 24;
    uint32_t word = compact & 0x007fffff;
    if (size <= 3) {
        word >>= 8 * (3 - size);
        *this = Uint256{word};
    } else {
        *this = Uint256{word};
        *this <<= 8 * (size - 3);
    }
    if (negative)
        *negative = word != 0 && (compact & 0x00800000) != 0;
    if (overflow)
        *overflow = word != 0 && ((size > 34) || (word > 0xff && size > 33) || (word > 0xffff && size > 32));
    return *this;
}

uint32_t Uint256::getCompact(bool negative) const {
    int32_t size = (this->bits() + 7) / 8;
    uint32_t compact = 0;
    if (size <= 3) {
        compact = this->getLow64() << 8 * (3 - size);
    } else {
        BaseUint<256> temp = *this >> 8 * (size - 3);
        compact = temp.getLow64();
    }
    if (compact & 0x00800000) {
        compact >>= 8;
        size++;
    }
    assert((compact & ~0x007fffff) == 0);
    assert(size < 256);
    compact |= size << 24;
    compact |= (negative && (compact & 0x007fffff) ? 0x00800000 : 0);
    return compact;
}

Blob256 arithToBlob256(const Uint256 &uint) {
    Blob256 blob;
    for (int32_t i = 0; i < Uint256::WIDTH; ++i)
        util::encode::WriteLE32(blob.begin() + i * 4, uint.data[i]);
    return blob;
}

Uint256 blobToArith256(const Blob256 &blob) {
    Uint256 uint;
    for (int32_t i = 0; i < Uint256::WIDTH; ++i)
        uint.data[i] = util::encode::ReadLE32(blob.begin() + i * 4);
    return uint;
}
