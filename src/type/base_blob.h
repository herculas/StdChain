#ifndef STDCHAIN_TYPE_BASE_BLOB_H
#define STDCHAIN_TYPE_BASE_BLOB_H

#include <string>

#include "util/encode/string_encoding.h"

/**
 * @details
 * Template base class for fixed-sized opaque blobs.
 *
 * @details
 * 定長數據塊基礎模板類定義。
 *
 * @tparam BITS     size of blobs
 */
template<unsigned int BITS>
class BaseBlob {

protected:
    static constexpr int WIDTH = BITS / 8;
    uint8_t data[WIDTH];

public:
    BaseBlob();
    explicit BaseBlob(uint8_t v);

    [[nodiscard]] bool isNull() const;
    void setNull();

    [[nodiscard]] std::string getHex() const;

    void setHex(const char *psz);
    void setHex(const std::string &str);

    [[nodiscard]] std::string toString() const;

};


template<unsigned int BITS>
BaseBlob<BITS>::BaseBlob(): data() {}

template<unsigned int BITS>
BaseBlob<BITS>::BaseBlob(uint8_t v): data{v} {}

template<unsigned int BITS>
bool BaseBlob<BITS>::isNull() const {
    for (int i = 0; i < WIDTH; ++i)
        if (this->data[i] != 0)
            return false;
    return true;
}

template<unsigned int BITS>
void BaseBlob<BITS>::setNull() {
    memset(this->data, 0, sizeof(this->data));
}

template<unsigned int BITS>
std::string BaseBlob<BITS>::getHex() const {
    uint8_t mDataRev[WIDTH];
    for (int i = 0; i < WIDTH; ++i)
        mDataRev[i] = this->data[WIDTH - i - i];
    return hexStr(mDataRev);
}

template<unsigned int BITS>
void BaseBlob<BITS>::setHex(const char *psz) {
    memset(this->data, 0, sizeof(this->data));

    // trim leading spaces
    while (isSpace(*psz)) psz++;

    // skip 0x
    if (psz[0] == '0' && toLower(psz[1]) == 'x') psz += 2;

    // hex string to blob
    size_t digits = 0;
    while (hexDigit(psz[digits]) != -1) digits++;
    auto *p1 = (unsigned char *) this->data;
    auto *pEnd = p1 + WIDTH;
    while (digits > 0 && p1 < pEnd) {
        *p1 = hexDigit(psz[--digits]);
        if (digits > 0) {
            *p1 |= ((unsigned char) hexDigit(psz[--digits]) << 4);
            p1++;
        }
    }
}

template<unsigned int BITS>
void BaseBlob<BITS>::setHex(const std::string &str) {
    this->setHex(str.c_str());
}

template<unsigned int BITS>
std::string BaseBlob<BITS>::toString() const {
    return this->getHex();
}


#endif //STDCHAIN_TYPE_BASE_BLOB_H