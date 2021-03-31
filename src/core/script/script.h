#ifndef STDCHAIN_CORE_SCRIPT_H
#define STDCHAIN_CORE_SCRIPT_H

#include <vector>
#include "boost/serialization/vector.hpp"
#include "core/script/op_code_type.h"
#include "core/script/script_num.h"

typedef std::vector<unsigned char> ScriptBase;

class Script : public ScriptBase {

protected:
    Script &pushInt64(int64_t n);

public:
    Script();
    Script(const_iterator begin, const_iterator end);
    Script(const unsigned char *begin, const unsigned char *end);
    explicit Script(int64_t base);
    explicit Script(OpCodeType base);
    explicit Script(const ScriptNum &base);
    Script(const std::vector<unsigned char> &base) = delete;

    bool getOp(const_iterator &iterator, OpCodeType &opCode, std::vector<unsigned char> vch) const;
    bool getOp(const_iterator &iterator, OpCodeType &opCode) const;

    static int32_t decodeOp(OpCodeType opCode);
    static OpCodeType encodeOp(int32_t n);

    [[nodiscard]] uint32_t getSigOpCount(bool accurate) const;
    [[nodiscard]] uint32_t getSigOpCount(const Script &scriptSig) const;

    [[nodiscard]] bool isPayToScriptHash() const;
    [[nodiscard]] bool isPayToWitnessScriptHash() const;
    [[nodiscard]] bool isPushOnly(const_iterator iterator) const;
    [[nodiscard]] bool isPushOnly() const;
    [[nodiscard]] bool hasValidOps() const;
    [[nodiscard]] bool isUnspendable() const;
    bool isWitnessProgram(int32_t &version, std::vector<unsigned char> &program) const;

    void clear();

    Script &operator<<(const Script &base) = delete;
    Script &operator<<(int64_t base);
    Script &operator<<(OpCodeType base);
    Script &operator<<(const ScriptNum &base);
    Script &operator<<(const std::vector<unsigned char> &base);

private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &archive, uint32_t version);

};

template<typename Archive>
void Script::serialize(Archive &archive, uint32_t version) {
    archive & boost::serialization::base_object<ScriptBase>(*this);
}

#endif //STDCHAIN_SCRIPT_H
