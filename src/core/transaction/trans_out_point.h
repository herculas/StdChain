#ifndef STDCHAIN_CORE_TRANSACTION_OUT_POINT_H
#define STDCHAIN_CORE_TRANSACTION_OUT_POINT_H

#include "type/blob/blob_256.h"

class OutPoint {

public:
    static constexpr uint32_t NULL_INDEX = std::numeric_limits<uint32_t>::max();

public:
    uint32_t n;
    Blob256 hash;

public:
    OutPoint();
    OutPoint(const Blob256 &hash, uint32_t n);

    void setNull();
    [[nodiscard]] bool isNull() const;
    [[nodiscard]] std::string toString() const;

    // TODO: serialize

    friend bool operator<(const OutPoint &a, const OutPoint &b);
    friend bool operator==(const OutPoint &a, const OutPoint &b);
    friend bool operator!=(const OutPoint &a, const OutPoint &b);

};


#endif //STDCHAIN_CORE_TRANSACTION_OUT_POINT_H
