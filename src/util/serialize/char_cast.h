#ifndef STDCHAIN_UTIL_SERIALIZE_CHAR_CAST_H
#define STDCHAIN_UTIL_SERIALIZE_CHAR_CAST_H

namespace util::serialize {
    inline char *charCast(char *c) {
        return c;
    }

    inline char *charCast(unsigned char *c) {
        return (char *) c;
    }

    inline const char *charCast(const char *c) {
        return c;
    }

    inline const char *charCast(const unsigned char *c) {
        return (const char *) c;
    }
} // namespace util::serialize

#endif //STDCHAIN_UTIL_SERIALIZE_CHAR_CAST_H
