#include "util/encode/string_encoding.h"

signed char hexDigit(char c) {
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

bool isHex(const std::string &str) {
    for (char c : str)
        if (hexDigit(c) < 0)
            return false;
    return !str.empty() && str.size() % 2 == 0;
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isSpace(char c) noexcept {
    return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v';
}

std::string hexStr(std::span<uint8_t> s) {
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

char toLower(char c) {
    return c >= 'A' && c <= 'Z' ? static_cast<char>(static_cast<int>(c) + 32) : c;
}

std::string toLower(const std::string &str) {
    std::string res;
    for (char c : str) res += toLower(c);
    return res;
}

char toUpper(char c) {
    return c >= 'a' && c <= 'z' ? static_cast<char>(static_cast<int>(c) + 32) : c;
}

std::string toUpper(const std::string &str) {
    std::string res;
    for (char c : str) res += toUpper(c);
    return res;
}

std::string capitalize(std::string &str) {
    if (str.empty()) return str;
    str[0] = toUpper(str.front());
    return str;
}
