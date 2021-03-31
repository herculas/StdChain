#include "core/script/script_num.h"

#include <stdexcept>

ScriptNum::ScriptNum(const int64_t &n) : value{n} {}

ScriptNum::ScriptNum(const std::vector<unsigned char> &vch, bool requiredMinimal, const size_t maxNumSize) {
    if (vch.size() > maxNumSize)
        throw std::runtime_error("ScriptNum: script number overflow.");
    if (requiredMinimal && !vch.empty())
        if ((vch.back() & 0x7f) == 0)
            if (vch.size() <= 1 || (vch[vch.size() - 2] & 0x80) == 0)
                throw std::runtime_error("ScriptNum: non-minimally encoded script number.");
    this->value = ScriptNum::setVch(vch);
}

int32_t ScriptNum::getInt() const {
    if (this->value > std::numeric_limits<int32_t>::max())
        return std::numeric_limits<int32_t>::max();
    else if (this->value < std::numeric_limits<int32_t>::min())
        return std::numeric_limits<int32_t>::min();
    return this->value;
}

std::vector<unsigned char> ScriptNum::getVch() const {
    return ScriptNum::serialize(this->value);
}

std::vector<unsigned char> ScriptNum::serialize(const int64_t &value) {
    if (value == 0) return std::vector<unsigned char>();
    std::vector<unsigned char> res;
    const bool neg = value < 0;
    uint64_t absValue = neg ? ~static_cast<uint64_t>(value) + 1 : static_cast<uint64_t>(value);
    while (absValue) {
        res.push_back(absValue & 0xff);
        absValue >>= 8;
    }
    if (res.back() & 0x80) res.push_back(neg ? 0x80 : 0);
    else if (neg) res.back() |= 0x80;
    return res;
}

int64_t ScriptNum::setVch(const std::vector<unsigned char> &vch) {
    if (vch.empty()) return 0;
    int64_t res = 0;
    for (int32_t i = 0; i != vch.size(); ++i)
        res |= static_cast<int64_t>(vch[i]) << 8 * i;
    if (vch.back() & 0x80)
        return -((int64_t) (res & ~(0x80ULL << (8 * (vch.size() - 1)))));
    return res;
}
