#include "util/encode/string_encoding.h"

signed char util::encode::hexDigit(char c) {
    const signed char utilHexDigit[256] = {
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1, -1, -1, -1, -1,
            -1, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    };
    return utilHexDigit[static_cast<unsigned char>(c)];
}

bool util::encode::isHex(const std::string &str) {
    for (char c : str)
        if (hexDigit(c) < 0)
            return false;
    return !str.empty() && str.size() % 2 == 0;
}

bool util::encode::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool util::encode::isSpace(char c) noexcept {
    return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v';
}

std::string util::encode::hexStr(std::span<uint8_t> s) {
    std::string res;
    static constexpr char hexMap[16] = {
            '0', '1', '2', '3',
            '4', '5', '6', '7',
            '8', '9', 'a', 'b',
            'c', 'd', 'e', 'f'
    };
    res.reserve(s.size() * 2);
    for (uint8_t v : s) {
        res.push_back(hexMap[v >> 4]);
        res.push_back(hexMap[v & 15]);
    }
    return res;
}

char util::encode::toLower(char c) {
    return c >= 'A' && c <= 'Z' ? static_cast<char>(static_cast<int>(c) + 32) : c;
}

std::string util::encode::toLower(const std::string &str) {
    std::string res;
    for (char c : str) res += toLower(c);
    return res;
}

char util::encode::toUpper(char c) {
    return c >= 'a' && c <= 'z' ? static_cast<char>(static_cast<int>(c) + 32) : c;
}

std::string util::encode::toUpper(const std::string &str) {
    std::string res;
    for (char c : str) res += toUpper(c);
    return res;
}

std::string util::encode::capitalize(std::string &str) {
    if (str.empty()) return str;
    str[0] = toUpper(str.front());
    return str;
}
