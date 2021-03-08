#ifndef STDCHAIN_CORE_TRANSACTION_OUT_POINT_H
#define STDCHAIN_CORE_TRANSACTION_OUT_POINT_H

#include "type/blob/blob_256.h"
#include "util/serialize/serialize.h"

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

    template<typename Stream>
    void serialize(Stream &stream) const;

    friend bool operator<(const OutPoint &a, const OutPoint &b);
    friend bool operator==(const OutPoint &a, const OutPoint &b);
    friend bool operator!=(const OutPoint &a, const OutPoint &b);

};

template<typename Stream>
void OutPoint::serialize(Stream &stream) const {
    static_assert(std::is_same<const OutPoint&, decltype(*this)>::value, "Serialize type mismatch");
    util::serialize::serializeMany(stream,
                                   this->hash,
                                   this->n);
}

#endif //STDCHAIN_CORE_TRANSACTION_OUT_POINT_H
