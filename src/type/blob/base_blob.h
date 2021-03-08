#ifndef STDCHAIN_TYPE_BLOB_BASE_BLOB_H
#define STDCHAIN_TYPE_BLOB_BASE_BLOB_H

#include <string>
#include <vector>
//#include "util/encode/string_encoding.h"

template<unsigned int BITS>
class BaseBlob {

protected:
    static constexpr int WIDTH = BITS / 8;
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
    [[nodiscard]] unsigned int size() const;
    [[nodiscard]] uint64_t getUint64(int pos) const;

    template<typename Stream>
    void serialize(Stream &stream) const;
    template<typename Stream>
    void deserialize(Stream &stream);

    inline int compare(const BaseBlob &other) const;
    friend inline bool operator==(const BaseBlob &a, const BaseBlob &b) { return a.compare(b) == 0; }
    friend inline bool operator!=(const BaseBlob &a, const BaseBlob &b) { return a.compare(b) != 0; }
    friend inline bool operator<(const BaseBlob &a, const BaseBlob &b) { return a.compare(b) < 0; }
};


template<unsigned int BITS>
BaseBlob<BITS>::BaseBlob(): data{} {}

template<unsigned int BITS>
BaseBlob<BITS>::BaseBlob(uint8_t v): data{v} {}

template<unsigned int BITS>
BaseBlob<BITS>::BaseBlob(const std::vector<unsigned char> &vch): data{} {
    assert(vch.size() == sizeof(this->data));
    memcpy(this->data, vch.data(), sizeof(this->data));
}

template<unsigned int BITS>
void BaseBlob<BITS>::setNull() {
    memset(this->data, 0, sizeof(this->data));
}

template<unsigned int BITS>
bool BaseBlob<BITS>::isNull() const {
    for (int i = 0; i < WIDTH; ++i)
        if (this->data[i] != 0)
            return false;
    return true;
}

template<unsigned int BITS>
void BaseBlob<BITS>::setHex(const char *psz) {
    // TODO
//    memset(this->data, 0, sizeof(this->data));
//
//    // trim leading spaces
//    while (util::encode::isSpace(*psz)) psz++;
//
//    // skip 0x
//    if (psz[0] == '0' && util::encode::toLower(psz[1]) == 'x') psz += 2;
//
//    // hex string to blob
//    size_t digits = 0;
//    while (util::encode::hexDigit(psz[digits]) != -1) digits++;
//    auto *p1 = (unsigned char *) this->data;
//    auto *pEnd = p1 + WIDTH;
//    while (digits > 0 && p1 < pEnd) {
//        *p1 = util::encode::hexDigit(psz[--digits]);
//        if (digits > 0) {
//            *p1 |= ((unsigned char) util::encode::hexDigit(psz[--digits]) << 4);
//            p1++;
//        }
//    }
}

template<unsigned int BITS>
void BaseBlob<BITS>::setHex(const std::string &str) {
    this->setHex(str.c_str());
}

template<unsigned int BITS>
std::string BaseBlob<BITS>::getHex() const {
    // TODO
    return std::string("BaseBlob::getHex");
//    uint8_t mDataRev[WIDTH];
//    for (int i = 0; i < WIDTH; ++i)
//        mDataRev[i] = this->data[WIDTH - i - i];
//    return util::encode::hexStr(mDataRev);
}

template<unsigned int BITS>
std::string BaseBlob<BITS>::toString() const {
    return this->getHex();
}

template<unsigned int BITS>
const unsigned char *BaseBlob<BITS>::getData() const {
    return this->data;
}

template<unsigned int BITS>
unsigned char *BaseBlob<BITS>::getData() {
    return this->data;
}

template<unsigned int BITS>
unsigned char *BaseBlob<BITS>::begin() {
    return &this->data[0];
}

template<unsigned int BITS>
unsigned char *BaseBlob<BITS>::end() {
    return &this->data[WIDTH];
}

template<unsigned int BITS>
const unsigned char *BaseBlob<BITS>::begin() const {
    return &this->data[0];
}

template<unsigned int BITS>
const unsigned char *BaseBlob<BITS>::end() const {
    return &this->data[WIDTH];
}

template<unsigned int BITS>
unsigned int BaseBlob<BITS>::size() const {
    return sizeof(this->data);
}

template<unsigned int BITS>
uint64_t BaseBlob<BITS>::getUint64(int pos) const {
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

template<unsigned int BITS>
template<typename Stream>
void BaseBlob<BITS>::serialize(Stream &stream) const {
    stream.write((char *) this->data, sizeof(this->data));
}

template<unsigned int BITS>
template<typename Stream>
void BaseBlob<BITS>::deserialize(Stream &stream) {
    stream.read((char *) this->data, sizeof(this->data));
}

template<unsigned int BITS>
int BaseBlob<BITS>::compare(const BaseBlob &other) const {
    return memcmp(this->data, other.data, sizeof(this->data));
}

#endif //STDCHAIN_TYPE_BLOB_BASE_BLOB_H
