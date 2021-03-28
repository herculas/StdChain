#ifndef STDCHAIN_TYPE_BLOB_BASE_BLOB_H
#define STDCHAIN_TYPE_BLOB_BASE_BLOB_H

#include <string>
#include <vector>
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"
#include "util/encode/string_encoding.h"

template<uint32_t BITS>
class BaseBlob {

protected:
    static constexpr int32_t WIDTH = BITS / 8;
    uint8_t data[WIDTH];

public:
    BaseBlob();
    explicit BaseBlob(uint8_t v);
    explicit BaseBlob(const std::vector<unsigned char> &vch);

    void setNull();
    [[nodiscard]] bool isNull() const;
    void setHex(const char *psz);
    void setHex(const std::string &str);
    [[nodiscard]] std::string getHex() const;
    [[nodiscard]] std::string toString() const;

    [[nodiscard]] const unsigned char *getData() const;
    unsigned char *getData();
    unsigned char *begin();
    unsigned char *end();
    [[nodiscard]] const unsigned char *begin() const;
    [[nodiscard]] const unsigned char *end() const;
    [[nodiscard]] uint32_t size() const;
    [[nodiscard]] uint64_t getUint64(int32_t pos) const;
    inline int32_t compare(const BaseBlob &other) const;

public:
    friend inline bool operator==(const BaseBlob &a, const BaseBlob &b) { return a.compare(b) == 0; }
    friend inline bool operator!=(const BaseBlob &a, const BaseBlob &b) { return a.compare(b) != 0; }
    friend inline bool operator<(const BaseBlob &a, const BaseBlob &b) { return a.compare(b) < 0; }

private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive& archive, uint32_t version);

};


template<uint32_t BITS>
BaseBlob<BITS>::BaseBlob(): data{} {}

template<uint32_t BITS>
BaseBlob<BITS>::BaseBlob(uint8_t v): data{v} {}

template<uint32_t BITS>
BaseBlob<BITS>::BaseBlob(const std::vector<unsigned char> &vch): data{} {
    assert(vch.size() == sizeof(this->data));
    memcpy(this->data, vch.data(), sizeof(this->data));
}

template<uint32_t BITS>
void BaseBlob<BITS>::setNull() {
    memset(this->data, 0, sizeof(this->data));
}

template<uint32_t BITS>
bool BaseBlob<BITS>::isNull() const {
    for (int32_t i = 0; i < WIDTH; ++i)
        if (this->data[i] != 0)
            return false;
    return true;
}

template<uint32_t BITS>
void BaseBlob<BITS>::setHex(const char *psz) {
    memset(this->data, 0, sizeof(this->data));

    // trim leading spaces
    while (util::encode::isSpace(*psz)) psz++;

    // skip 0x
    if (psz[0] == '0' && util::encode::toLower(psz[1]) == 'x') psz += 2;

    // hex string to blob
    size_t digits = 0;
    while (util::encode::hexDigit(psz[digits]) != -1) digits++;
    auto *p1 = (unsigned char *) this->data;
    auto *pEnd = p1 + WIDTH;
    while (digits > 0 && p1 < pEnd) {
        *p1 = util::encode::hexDigit(psz[--digits]);
        if (digits > 0) {
            *p1 |= ((unsigned char) util::encode::hexDigit(psz[--digits]) << 4);
            p1++;
        }
    }
}

template<uint32_t BITS>
void BaseBlob<BITS>::setHex(const std::string &str) {
    this->setHex(str.c_str());
}

template<uint32_t BITS>
std::string BaseBlob<BITS>::getHex() const {
    uint8_t mDataRev[WIDTH];
    for (int32_t i = 0; i < WIDTH; ++i) {
        int32_t newIndex = WIDTH - i - 1;
        mDataRev[i] = this->data[newIndex];
    }
    return util::encode::hexStr(mDataRev);
}

template<uint32_t BITS>
std::string BaseBlob<BITS>::toString() const {
    return this->getHex();
}

template<uint32_t BITS>
const unsigned char *BaseBlob<BITS>::getData() const {
    return this->data;
}

template<uint32_t BITS>
unsigned char *BaseBlob<BITS>::getData() {
    return this->data;
}

template<uint32_t BITS>
unsigned char *BaseBlob<BITS>::begin() {
    return &this->data[0];
}

template<uint32_t BITS>
unsigned char *BaseBlob<BITS>::end() {
    return &this->data[WIDTH];
}

template<uint32_t BITS>
const unsigned char *BaseBlob<BITS>::begin() const {
    return &this->data[0];
}

template<uint32_t BITS>
const unsigned char *BaseBlob<BITS>::end() const {
    return &this->data[WIDTH];
}

template<uint32_t BITS>
uint32_t BaseBlob<BITS>::size() const {
    return sizeof(this->data);
}

template<uint32_t BITS>
uint64_t BaseBlob<BITS>::getUint64(int32_t pos) const {
    const uint8_t *ptr = this->data + pos * 8;
    return
        ((uint64_t)ptr[0]) | \
        ((uint64_t)ptr[1]) << 8 | \
        ((uint64_t)ptr[2]) << 16 | \
        ((uint64_t)ptr[3]) << 24 | \
        ((uint64_t)ptr[4]) << 32 | \
        ((uint64_t)ptr[5]) << 40 | \
        ((uint64_t)ptr[6]) << 48 | \
        ((uint64_t)ptr[7]) << 56;
}

template<uint32_t BITS>
int32_t BaseBlob<BITS>::compare(const BaseBlob &other) const {
    return memcmp(this->data, other.data, sizeof(this->data));
}

template<uint32_t BITS>
template<typename Archive>
void BaseBlob<BITS>::serialize(Archive &archive, const uint32_t version) {
    archive & this->data;
}

#endif //STDCHAIN_TYPE_BLOB_BASE_BLOB_H
