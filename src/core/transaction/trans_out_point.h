#ifndef STDCHAIN_CORE_TRANSACTION_OUTPUT_POINT_H
#define STDCHAIN_CORE_TRANSACTION_OUTPUT_POINT_H

#include <string>
#include "type/blob/blob_256.h"

class TxOutPoint {

public:
    static constexpr uint32_t NULL_INDEX = std::numeric_limits<uint32_t>::max();

public:
    uint32_t n;
    Blob256 hash;

public:
    TxOutPoint();
    TxOutPoint(uint32_t n, Blob256 &hash);

    void setNull();
    [[nodiscard]] bool isNull() const;
    [[nodiscard]] std::string toString() const;

    friend bool operator<(const TxOutPoint &a, const TxOutPoint &b);
    friend bool operator==(const TxOutPoint &a, const TxOutPoint &b);
    friend bool operator!=(const TxOutPoint &a, const TxOutPoint &b);

};


#endif //STDCHAIN_CORE_TRANSACTION_OUTPUT_POINT_H
