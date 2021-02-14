#ifndef STDCHAIN_UTIL_ENCODE_STRING_ENCODING_H
#define STDCHAIN_UTIL_ENCODE_STRING_ENCODING_H

#include <span>
#include <string>

signed char hexDigit(char c);

/**
 * Returns true if each character in @b str is a hex character, and has an @b
 * even number of hex digits.
 */
bool isHex(const std::string &str);

/**
 * Tests if the given character is a decimal digit.
 * @param c     character to test
 * @return      true if the argument is a decimal digit; otherwise false.
 */
bool isDigit(char c);

/**
 * @paragraph
 * Tests if the given character is a whitespace character. The whitespace characters
 * are: space, form-feed, newline, carriage return, horizontal tab, and vertical tab.
 *
 * @paragraph
 * This function is locale independent. Under the C locale this function given the
 * same result as std::isspace.
 *
 * @param c     character to test
 * @return      true if the argument is a whitespace character; otherwise false
 */
bool isSpace(char c) noexcept;

/**
 * Converts a span of bytes to a lower-case hexadecimal string.
 */
std::string hexStr(std::span<uint8_t> s);

/**
 * Converts the given character to its lowercase equivalent. This function is locale
 * independent. It only converts uppercase characters in the standard 7-bit ASCII
 * range. This is a feature, not a limitation.
 */
char toLower(char c);
std::string toLower(const std::string &str);

/**
 * Converts the given character to its uppercase equivalent. This function is locale
 * independent. It only converts lowercase characters in the standard 7-bit ASCII
 * range. This is a feature, not a limitation.
 */
char toUpper(char c);
std::string toUpper(const std::string &str);

/**
 * Capitalizes the first character of the given string. This function is locale
 * independent. It only converts lowercase characters in the standard 7-bit ASCII
 * range. This is a feature, not a limitation.
 *
 * @param str   the string to capitalize
 * @return      string with the first letter capitalized
 */
std::string capitalize(std::string& str);

#endif //STDCHAIN_UTIL_ENCODE_STRING_ENCODING_H
