#ifndef STDCHAIN_UTIL_SERIALIZE_LOW_LEVEL_CONVERSION_H
#define STDCHAIN_UTIL_SERIALIZE_LOW_LEVEL_CONVERSION_H

#include "util/compact/endian.h"

namespace util::serialize {

    template<typename Stream>
    inline void writeData8(Stream &stream, uint8_t object) {
        stream.write((char *) &object, 1);
    }

    template<typename Stream>
    inline void writeData16(Stream &stream, uint16_t object) {
        object = util::compact::htole16(object);
        stream.write((char *) &object, 2);
    }

    template<typename Stream>
    inline void writeData16BE(Stream &stream, uint16_t object) {
        object = util::compact::htobe16(object);
        stream.write((char *) &object, 2);
    }

    template<typename Stream>
    inline void writeData32(Stream &stream, uint32_t object) {
        object = util::compact::htole32(object);
        stream.write((char *) &object, 4);
    }

    template<typename Stream>
    inline void writeData32BE(Stream &stream, uint32_t object) {
        object = util::compact::htobe32(object);
        stream.write((char *) &object, 4);
    }

    template<typename Stream>
    inline void writeData64(Stream &stream, uint64_t object) {
        object = util::compact::htole64(object);
        stream.write((char *) &object, 8);
    }

    template<typename Stream>
    inline uint8_t readData8(Stream &stream) {
        uint8_t object;
        stream.read((char *) &object, 1);
        return object;
    }

    template<typename Stream>
    inline uint16_t readData16(Stream &stream) {
        uint16_t object;
        stream.read((char *) &object, 2);
        return util::compact::le16toh(object);
    }

    template<typename Stream>
    inline uint16_t readData16BE(Stream &stream) {
        uint16_t object;
        stream.read((char *) &object, 2);
        return util::compact::be16toh(object);
    }

    template<typename Stream>
    inline uint32_t readData32(Stream &stream) {
        uint32_t object;
        stream.read((char *) &object, 4);
        return util::compact::le32toh(object);
    }

    template<typename Stream>
    inline uint32_t readData32BE(Stream &stream) {
        uint32_t object;
        stream.read((char *) &object, 4);
        return util::compact::be32toh(object);
    }

    template<typename Stream>
    inline uint64_t readData64(Stream &stream) {
        uint64_t object;
        stream.read((char *) &object, 8);
        return util::compact::le64toh(object);
    }

    inline uint64_t floatToUint32(float x) {
        uint32_t y;
        std::memcpy(&y, &x, sizeof(x));
        static_assert(sizeof(y) == sizeof(x), "float and uint32_t assumed to have the same size.");
        return y;
    }

    inline uint64_t doubleToUint64(double x) {
        uint64_t y;
        std::memcpy(&y, &x, sizeof(x));
        static_assert(sizeof(y) == sizeof(x), "double and uint64_t assumed to have the same size.");
        return y;
    }

    inline float uint32ToFloat(uint32_t y) {
        float x;
        std::memcpy(&x, &y, sizeof(y));
        static_assert(sizeof(x) == sizeof(y), "float and uint32_t assumed to have the same size.");
        return x;
    }

    inline double uint64ToDouble(uint64_t y) {
        double x;
        std::memcpy(&x, &y, sizeof(y));
        static_assert(sizeof(x) == sizeof(y), "double and uint64_t assumed to have the same size.");
        return x;
    }

} // namespace util::serialize

#endif //STDCHAIN_UTIL_SERIALIZE_LOW_LEVEL_CONVERSION_H
