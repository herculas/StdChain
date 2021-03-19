#ifndef STDCHAIN_TYPE_ARITH_UINT_256_H
#define STDCHAIN_TYPE_ARITH_UINT_256_H

#include <string>
#include "type/arith/base_uint.h"
#include "type/blob/blob_256.h"

class Uint256 : public BaseUint<256> {

public:
    Uint256();
    explicit Uint256(const BaseUint<256> &base);
    explicit Uint256(uint64_t base);
    explicit Uint256(const std::string &str);

    Uint256 &setCompact(uint32_t compact, bool *negative = nullptr, bool *overflow = nullptr);
    [[nodiscard]] uint32_t getCompact(bool negative = false) const;

    friend Blob256 arithToBlob256(const Uint256 &uint);
    friend Uint256 blobToArith256(const Blob256 &blob);

};

#endif //STDCHAIN_TYPE_ARITH_UINT_256_H
