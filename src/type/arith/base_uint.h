#ifndef STDCHAIN_TYPE_ARITH_BASE_UINT_H
#define STDCHAIN_TYPE_ARITH_BASE_UINT_H

#include <string>
#include <stdexcept>
#include "type/blob/base_blob.h"
#include "util/encode/common.h"

template<uint32_t BITS>
class BaseUint {

protected:
    static constexpr int32_t WIDTH = BITS / 32;
    uint32_t data[WIDTH];

public:
    BaseUint();
    BaseUint(const BaseUint &base);
    explicit BaseUint(uint64_t base);
    explicit BaseUint(const std::string &str);

    [[nodiscard]] double getDouble() const;
    [[nodiscard]] bool equalTo(uint64_t base) const;
    int32_t compareTo(const BaseUint &base) const;

    void setHex(const char *psz);
    void setHex(const std::string &str);
    [[nodiscard]] std::string getHex() const;
    [[nodiscard]] std::string toString() const;
    [[nodiscard]] uint32_t size() const;
    [[nodiscard]] uint32_t bits() const;
    [[nodiscard]] uint64_t getLow64() const;

public:
    BaseUint &operator=(const BaseUint &base);
    BaseUint &operator^=(const BaseUint &base);
    BaseUint &operator&=(const BaseUint &base);
    BaseUint &operator|=(const BaseUint &base);
    BaseUint &operator+=(const BaseUint &base);
    BaseUint &operator-=(const BaseUint &base);
    BaseUint &operator*=(const BaseUint &base);
    BaseUint &operator/=(const BaseUint &base);

    BaseUint &operator=(uint64_t base);
    BaseUint &operator^=(uint64_t base);
    BaseUint &operator|=(uint64_t base);
    BaseUint &operator+=(uint64_t base);
    BaseUint &operator-=(uint64_t base);
    BaseUint &operator*=(uint32_t base);

    BaseUint &operator<<=(uint32_t shift);
    BaseUint &operator>>=(uint32_t shift);

    BaseUint &operator++();
    BaseUint &operator--();
    const BaseUint operator++(int);
    const BaseUint operator--(int);
    const BaseUint operator~() const;
    const BaseUint operator-() const;

public:
    friend inline BaseUint operator+(const BaseUint &a, const BaseUint &b) { return BaseUint(a) += b; }
    friend inline BaseUint operator-(const BaseUint &a, const BaseUint &b) { return BaseUint(a) -= b; }
    friend inline BaseUint operator*(const BaseUint &a, const BaseUint &b) { return BaseUint(a) *= b; }
    friend inline BaseUint operator/(const BaseUint &a, const BaseUint &b) { return BaseUint(a) /= b; }
    friend inline BaseUint operator|(const BaseUint &a, const BaseUint &b) { return BaseUint(a) |= b; }
    friend inline BaseUint operator&(const BaseUint &a, const BaseUint &b) { return BaseUint(a) &= b; }
    friend inline BaseUint operator^(const BaseUint &a, const BaseUint &b) { return BaseUint(a) ^= b; }
    friend inline BaseUint operator>>(const BaseUint &a, int32_t shift) { return BaseUint(a) >>= shift; }
    friend inline BaseUint operator<<(const BaseUint &a, int32_t shift) { return BaseUint(a) <<= shift; }
    friend inline BaseUint operator*(const BaseUint &a, uint32_t b) { return BaseUint(a) *= b; }

    friend inline bool operator==(const BaseUint &a, const BaseUint &b) { return memcmp(a.data, b.data, sizeof(a.data)) == 0; }
    friend inline bool operator!=(const BaseUint &a, const BaseUint &b) { return memcmp(a.data, b.data, sizeof(a.data)) != 0; }
    friend inline bool operator>(const BaseUint &a, const BaseUint &b) { return a.compareTo(b) > 0; }
    friend inline bool operator<(const BaseUint &a, const BaseUint &b) { return a.compareTo(b) < 0; }
    friend inline bool operator>=(const BaseUint &a, const BaseUint &b) { return a.compareTo(b) >= 0; }
    friend inline bool operator<=(const BaseUint &a, const BaseUint &b) { return a.compareTo(b) <= 0; }
    friend inline bool operator==(const BaseUint &a, uint64_t b) { return a.equalTo(b); }
    friend inline bool operator!=(const BaseUint &a, uint64_t b) { return !a.equalTo(b); }

};

template<uint32_t BITS>
BaseUint<BITS>::BaseUint(): data() {
    static_assert(BITS / 32 > 0 && BITS % 32 == 0, "Template parameter BITS must be positive multiple of 32.");
    for (int32_t i = 0; i < WIDTH; ++i)
        this->data[i] = 0;
}

template<uint32_t BITS>
BaseUint<BITS>::BaseUint(const BaseUint &base): data() {
    static_assert(BITS / 32 > 0 && BITS % 32 == 0, "Template parameter BITS must be positive multiple of 32.");
    for (int32_t i = 0; i < WIDTH; ++i)
        this->data[i] = base.data[i];
}

template<uint32_t BITS>
BaseUint<BITS>::BaseUint(uint64_t base): data() {
    static_assert(BITS / 32 > 0 && BITS % 32 == 0, "Template parameter BITS must be positive multiple of 32.");
    this->data[0] = (uint32_t) base;
    this->data[1] = (uint32_t) (base >> 32);
    for (int32_t i = 0; i < WIDTH; ++i)
        this->data[i] = 0;
}

template<uint32_t BITS>
BaseUint<BITS>::BaseUint(const std::string &str): data() {
    static_assert(BITS / 32 > 0 && BITS % 32 == 0, "Template parameter BITS must be positive multiple of 32.");
    this->setHex(str);
}

template<uint32_t BITS>
double BaseUint<BITS>::getDouble() const {
    double res = 0.0;
    double fact = 1.0;
    for (int32_t i = 0; i < WIDTH; ++i) {
        res += fact * this->data[i];
        fact *= 4294967296.0;
    }
    return res;
}

template<uint32_t BITS>
bool BaseUint<BITS>::equalTo(uint64_t base) const {
    for (int32_t i = WIDTH - 1; i >= 2; i--)
        if (this->data[i])
            return false;

    if (this->data[1] != (base >> 32))
        return false;
    if (this->data[0] != (base & 0xfffffffful))
        return false;
    return true;
}

template<uint32_t BITS>
int32_t BaseUint<BITS>::compareTo(const BaseUint<BITS> &base) const {
    for (int32_t i = WIDTH - 1; i >= 0; i--) {
        if (this->data[i] < base.data[i])
            return -1;
        if (this->data[i] > base.data[i])
            return 1;
    }
    return 0;
}

template<uint32_t BITS>
void BaseUint<BITS>::setHex(const char *psz) {
    BaseBlob<BITS> blob;
    BaseUint<BITS> uint;
    blob.setHex(psz);
    for (int32_t i = 0; i < uint.WIDTH; ++i)
        uint.data[i] = util::encode::ReadLE32(blob.begin() + i * 4);
    *this = uint;
}

template<uint32_t BITS>
void BaseUint<BITS>::setHex(const std::string &str) {
    this->setHex(str.c_str());
}

template<uint32_t BITS>
std::string BaseUint<BITS>::getHex() const {
    BaseBlob<BITS> blob;
    for (int32_t i = 0; i < this->WIDTH; ++i)
        util::encode::WriteLE32(blob.begin() + i * 4, this->data[i]);
    return blob.getHex();
}

template<uint32_t BITS>
std::string BaseUint<BITS>::toString() const {
    return this->getHex();
}

template<uint32_t BITS>
uint32_t BaseUint<BITS>::size() const {
    return sizeof(this->data);
}

template<uint32_t BITS>
uint32_t BaseUint<BITS>::bits() const {
    for (int32_t pos = WIDTH - 1; pos >= 0; pos--) {
        if (this->data[pos]) {
            for (int32_t bits = 31; bits > 0; bits--) {
                if (this->data[pos] & 1U << bits)
                    return 32 * pos + bits + 1;
            }
            return 32 * pos + 1;
        }
    }
    return 0;
}

template<uint32_t BITS>
uint64_t BaseUint<BITS>::getLow64() const {
    static_assert(WIDTH >= 2, "Object less than 64 bits.");
    return this->data[0] | (uint64_t) this->data[1] << 32;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator=(const BaseUint &base) {
    if (this == &base) return *this;
    for (int32_t i = 0; i < WIDTH; ++i)
        this->data[i] = base.data[i];
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator^=(const BaseUint &base) {
    for (int32_t i = 0; i < WIDTH; ++i)
        this->data[i] ^= base.data[i];
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator&=(const BaseUint &base) {
    for (int32_t i = 0; i < WIDTH; ++i)
        this->data[i] &= base.data[i];
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator|=(const BaseUint &base) {
    for (int32_t i = 0; i < WIDTH; ++i)
        this->data[i] |= base.data[i];
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator+=(const BaseUint &base) {
    uint64_t carry = 0;
    for (int32_t i = 0; i < WIDTH; ++i) {
        uint64_t n = carry + this->data[i] + base.data[i];
        this->data[i] = n & 0xffffffff;
        carry = n >> 32;
    }
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator-=(const BaseUint &base) {
    *this += -base;
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator*=(const BaseUint &base) {
    BaseUint<BITS> res;
    for (int32_t j = 0; j < WIDTH; ++j) {
        uint64_t carry = 0;
        for (int32_t i = 0; i + j < WIDTH; ++i) {
            uint64_t n = carry + res.data[i + j] + (uint64_t) this->data[j] * base.data[i];
            res.data[i + j] = n & 0xffffffff;
            carry = n >> 32;
        }
    }
    *this = res;
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator/=(const BaseUint &base) {
    BaseUint<BITS> div = base;
    BaseUint<BITS> num = *this;
    *this = 0;
    int32_t numBits = num.bits();
    int32_t divBits = div.bits();
    if (divBits == 0) throw std::runtime_error("Division by 0.");
    if (divBits > numBits) return *this;
    int32_t shift = numBits - divBits;
    div << shift;
    while (shift >= 0) {
        if (num >= div) {
            num -= div;
            this->data[shift / 32] |= (1 << (shift & 31));
        }
        div >>= 1;
        shift--;
    }
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator=(uint64_t base) {
    this->data[0] = (uint32_t) base;
    this->data[1] = (uint32_t) (base >> 32);
    for (int32_t i = 2; i < WIDTH; ++i)
        this->data[0] = 0;
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator^=(uint64_t base) {
    this->data[0] ^= (uint32_t) base;
    this->data[1] ^= (uint32_t) (base >> 32);
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator|=(uint64_t base) {
    this->data[0] |= (uint32_t) base;
    this->data[1] |= (uint32_t) (base >> 32);
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator+=(uint64_t base) {
    BaseUint<BITS> temp;
    temp = base;
    *this += temp;
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator-=(uint64_t base) {
    BaseUint<BITS> temp;
    temp = base;
    *this += -temp;
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator*=(uint32_t base) {
    uint64_t carry = 0;
    for (int32_t i = 0; i < WIDTH; ++i) {
        uint64_t n = carry + (uint64_t) base * this->data[i];
        this->data[i] = n & 0xffffffff;
        carry = n >> 32;
    }
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator<<=(uint32_t shift) {
    BaseUint<BITS> temp{*this};
    for (int32_t i = 0; i < WIDTH; ++i) this->data[i] = 0;
    int32_t k = shift / 32;
    shift = shift % 32;
    for (int32_t i = 0; i < WIDTH; ++i) {
        if (i + k + 1 < WIDTH && shift != 0)
            this->data[i + k + 1] |= (temp.data[i] >> (32 - shift));
        if (i + k < WIDTH)
            this->data[i + k] |= (temp.data[i] << shift);
    }
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator>>=(uint32_t shift) {
    BaseUint<BITS> temp{*this};
    for (int32_t i = 0; i < WIDTH; ++i) this->data[i] = 0;
    int32_t k = shift / 32;
    shift = shift % 32;
    for (int32_t i = 0; i < WIDTH; ++i) {
        if (i - k - 1 >= 0 && shift != 0)
            this->data[i - k - 1] |= (temp.data[i] << (32 - shift));
        if (i - k >= 0)
            this->data[i - k] |= (temp.data[i] >> shift);
    }
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator++() {
    int32_t i = 0;
    while (i < WIDTH && ++this->data[i] == 0) i++;
    return *this;
}

template<uint32_t BITS>
BaseUint<BITS> &BaseUint<BITS>::operator--() {
    int32_t i = 0;
    while (i < WIDTH && --this->data[i] == std::numeric_limits<uint32_t>::max()) i++;
    return *this;
}

template<uint32_t BITS>
const BaseUint<BITS> BaseUint<BITS>::operator++(int) { // NOLINT(readability-const-return-type)
    const BaseUint<BITS> res = *this;
    ++(*this);
    return res;
}

template<uint32_t BITS>
const BaseUint<BITS> BaseUint<BITS>::operator--(int) { // NOLINT(readability-const-return-type)
    const BaseUint<BITS> res = *this;
    --(*this);
    return res;
}

template<uint32_t BITS>
const BaseUint<BITS> BaseUint<BITS>::operator~() const { // NOLINT(readability-const-return-type)
    BaseUint<BITS> res;
    for (int32_t i = 0; i < WIDTH; ++i)
        res.data[i] = ~this->data[i];
    return res;
}

template<uint32_t BITS>
const BaseUint<BITS> BaseUint<BITS>::operator-() const { // NOLINT(readability-const-return-type)
    BaseUint<BITS> res;
    for (int32_t i = 0; i < WIDTH; ++i)
        res.data[i] = ~this->data[i];
    ++res;
    return res;
}

#endif //STDCHAIN_TYPE_ARITH_BASE_UINT_H
