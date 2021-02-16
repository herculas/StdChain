#ifndef STDCHAIN_UTIL_ENCODE_STRING_ENCODING_H
#define STDCHAIN_UTIL_ENCODE_STRING_ENCODING_H

#include <span>
#include <string>

namespace util::encode {

    signed char hexDigit(char c);
    bool isHex(const std::string &str);
    bool isDigit(char c);
    bool isSpace(char c) noexcept;
    std::string hexStr(std::span<uint8_t> s);
    char toLower(char c);
    std::string toLower(const std::string &str);
    char toUpper(char c);
    std::string toUpper(const std::string &str);
    std::string capitalize(std::string &str);

} // namespace util::encode

#endif //STDCHAIN_UTIL_ENCODE_STRING_ENCODING_H
