#ifndef STDCHAIN_CORE_SCRIPT_NUM_H
#define STDCHAIN_CORE_SCRIPT_NUM_H

#include <cstdint>
#include <cstdlib>
#include <vector>

class ScriptNum {

private:
    static const size_t DEFAULT_MAX_NUM_SIZE = 4;
    int64_t value;

public:
    explicit ScriptNum(const int64_t &n);
    ScriptNum(const std::vector<unsigned char> &vch, bool requiredMinimal, size_t maxNumSize = DEFAULT_MAX_NUM_SIZE);

    [[nodiscard]] int32_t getInt() const;
    [[nodiscard]] std::vector<unsigned char> getVch() const;
    static std::vector<unsigned char> serialize(const int64_t &value);

private:
    static int64_t setVch(const std::vector<unsigned char> &vch);

public:
    inline bool operator==(const int64_t &rhs) const { return this->value == rhs; }
    inline bool operator!=(const int64_t &rhs) const { return this->value != rhs; }
    inline bool operator<=(const int64_t &rhs) const { return this->value <= rhs; }
    inline bool operator>=(const int64_t &rhs) const { return this->value >= rhs; }
    inline bool operator<(const int64_t &rhs) const { return this->value < rhs; }
    inline bool operator>(const int64_t &rhs) const { return this->value > rhs; }

    inline bool operator==(const ScriptNum &rhs) const { return operator==(rhs.value); }
    inline bool operator!=(const ScriptNum &rhs) const { return operator!=(rhs.value); }
    inline bool operator<=(const ScriptNum &rhs) const { return operator<=(rhs.value); }
    inline bool operator>=(const ScriptNum &rhs) const { return operator>=(rhs.value); }
    inline bool operator<(const ScriptNum &rhs) const { return operator<(rhs.value); }
    inline bool operator>(const ScriptNum &rhs) const { return operator>(rhs.value); }

    inline ScriptNum operator+(const int64_t &rhs) const { return ScriptNum(this->value + rhs); }
    inline ScriptNum operator-(const int64_t &rhs) const { return ScriptNum(this->value - rhs); }
    inline ScriptNum operator&(const int64_t &rhs) const { return ScriptNum(this->value & rhs); }

    inline ScriptNum operator+(const ScriptNum &rhs) const { return operator+(rhs.value); }
    inline ScriptNum operator-(const ScriptNum &rhs) const { return operator-(rhs.value); }
    inline ScriptNum operator&(const ScriptNum &rhs) const { return operator&(rhs.value); }

    inline ScriptNum &operator+=(const ScriptNum &rhs) { return operator+=(rhs.value); }
    inline ScriptNum &operator-=(const ScriptNum &rhs) { return operator-=(rhs.value); }
    inline ScriptNum &operator&=(const ScriptNum &rhs) { return operator&=(rhs.value); }

    inline ScriptNum operator-() const;
    inline ScriptNum &operator=(const int64_t &rhs);
    inline ScriptNum &operator+=(const int64_t &rhs);
    inline ScriptNum &operator-=(const int64_t &rhs);
    inline ScriptNum &operator&=(const int64_t &rhs);

};

ScriptNum ScriptNum::operator-() const {
    assert(this->value != std::numeric_limits<int64_t>::min());
    return ScriptNum(-this->value);
}

ScriptNum &ScriptNum::operator=(const int64_t &rhs) {
    this->value = rhs;
    return *this;
}

ScriptNum &ScriptNum::operator+=(const int64_t &rhs) {
    assert(rhs == 0 ||
           (rhs > 0 && this->value <= std::numeric_limits<int64_t>::max() - rhs) ||
           (rhs < 0 && this->value >= std::numeric_limits<int64_t>::min() - rhs));
    this->value += rhs;
    return *this;
}

ScriptNum &ScriptNum::operator-=(const int64_t &rhs) {
    assert(rhs == 0 ||
           (rhs > 0 && this->value >= std::numeric_limits<int64_t>::min() + rhs) ||
           (rhs < 0 && this->value <= std::numeric_limits<int64_t>::max() + rhs));
    this->value -= rhs;
    return *this;
}

ScriptNum &ScriptNum::operator&=(const int64_t &rhs) {
    this->value &= rhs;
    return *this;
}

#endif //STDCHAIN_CORE_SCRIPT_NUM_H
