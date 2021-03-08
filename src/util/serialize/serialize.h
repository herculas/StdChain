#ifndef STDCHAIN_UTIL_SERIALIZE_SERIALIZE_H
#define STDCHAIN_UTIL_SERIALIZE_SERIALIZE_H

#include <map>
#include <set>
#include <span>
#include <string>
#include <type_traits>
#include <vector>
#include "type/stream/wrapper.h"
#include "type/stream/vector_formatter.h"
#include "type/stream/default_formatter.h"
#include "util/serialize/char_cast.h"
#include "util/serialize/compact_size.h"
#include "util/serialize/low_level_conversion.h"

namespace util::serialize {

    template<typename Stream>
    inline void serialize(Stream &stream, int8_t a) {
        writeData8(stream, a);
    }

    template<typename Stream>
    inline void serialize(Stream &stream, uint8_t a) {
        writeData8(stream, a);
    }

    template<typename Stream>
    inline void serialize(Stream &stream, int16_t a) {
        writeData16(stream, a);
    }

    template<typename Stream>
    inline void serialize(Stream &stream, uint16_t a) {
        writeData16(stream, a);
    }

    template<typename Stream>
    inline void serialize(Stream &stream, int32_t a) {
        writeData32(stream, a);
    }

    template<typename Stream>
    inline void serialize(Stream &stream, uint32_t a) {
        writeData32(stream, a);
    }

    template<typename Stream>
    inline void serialize(Stream &stream, int64_t a) {
        writeData64(stream, a);
    }

    template<typename Stream>
    inline void serialize(Stream &stream, uint64_t a) {
        writeData64(stream, a);
    }

    template<typename Stream>
    inline void serialize(Stream &stream, float a) {
        writeData32(stream, floatToUint32(a));
    }

    template<typename Stream>
    inline void serialize(Stream &stream, double a) {
        writeData64(stream, doubleToUint64(a));
    }

    template<typename Stream>
    inline void serialize(Stream &stream, bool a) {
        char f = static_cast<char>(a);
        writeData8(stream, f);
    }

    template<typename Stream, int N>
    inline void serialize(Stream &stream, const char (&a)[N]) {
        stream.write(a, N);
    }

    template<typename Stream, int N>
    inline void serialize(Stream &stream, const unsigned char (&a)[N]) {
        stream.write(charCast(a), N);
    }

    template<typename Stream>
    inline void serialize(Stream &stream, const std::span<unsigned char> &span) {
        stream.write(charCast(span.data()), span.size());
    }

    template<typename Stream>
    inline void serialize(Stream &stream, const std::span<const unsigned char> &span) {
        stream.write(charCast(span.data()), span.size());
    }

    template<typename Stream, typename C>
    void serialize(Stream &stream, const std::basic_string<C> &string) {
        writeCompactSize(stream, string.size());
        if (!string.empty())
            stream.write((char *) string.data(), string.size() * sizeof(C));
    }

    template<typename Stream, typename T, typename A>
    void vectorSerializeImpl(Stream &stream, const std::vector<T, A> &vector, const unsigned char &) {
        writeCompactSize(stream, vector.size());
        if (!vector.empty())
            stream.write((char *) vector.data(), vector.size() * sizeof(T));
    }

    template<typename Stream, typename T, typename A>
    void vectorSerializeImpl(Stream &stream, const std::vector<T, A> &vector, const bool &) {
        writeCompactSize(stream, vector.size());
        for (bool element: vector) serialize(stream, element);
    }

    template<typename Stream, typename T, typename A, typename V>
    void vectorSerializeImpl(Stream &stream, const std::vector<T, A> &vector, const V &) {
        serialize(stream, usingWrapper<VectorFormatter<DefaultFormatter>>(vector));
    }

    template<typename Stream, typename T, typename A>
    inline void serialize(Stream &stream, const std::vector<T, A> &vector) {
        vectorSerializeImpl(stream, vector, T());
    }

    template<typename Stream, typename K, typename T>
    void serialize(Stream &stream, const std::pair<K, T> &pair) {
        serialize(stream, pair.first);
        serialize(stream, pair.second);
    }

    template<typename Stream, typename K, typename T, typename Pred, typename A>
    void serialize(Stream &stream, const std::map<K, T, Pred, A> &map) {
        writeCompactSize(stream, map.size());
        for (const auto &entry : map)
            serialize(stream, entry);
    }

    template<typename Stream, typename K, typename Pred, typename A>
    void serialize(Stream &stream, const std::set<K, Pred, A> &set) {
        writeCompactSize(stream, set.size());
        for (const auto &entry : set) {
            serialize(stream, entry);
        }
    }

    template<typename Stream, typename T>
    void serialize(Stream &stream, const std::shared_ptr<const T> &ptr) {
        serialize(stream, *ptr);
    }

    template<typename Stream, typename T>
    void serialize(Stream &stream, const std::unique_ptr<const T> &ptr) {
        serialize(stream, *ptr);
    }

    template<typename Stream, typename T>
    inline void serialize(Stream &stream, const T &a) {
        a.serialize(stream);
    }

    template<typename Stream>
    void serializeMany(Stream &stream) {}

    template<typename Stream, typename Arg, typename... Args>
    void serializeMany(Stream &stream, const Arg &arg, const Args &... args) {
        serialize(stream, arg);
        serializeMany(stream, args...);
    }

} // namespace util::serialize

#endif //STDCHAIN_UTIL_SERIALIZE_SERIALIZE_H
