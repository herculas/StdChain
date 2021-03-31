#include "core/script/script.h"

#include "config/script.h"
#include "util/encode/common.h"

Script &Script::pushInt64(int64_t n) {
    if (n == -1 || (n >= 1 && n <= 16))
        this->push_back(n + static_cast<unsigned char>(OpCodeType::OP_1) - 1);
    else if (n == 0)
        this->push_back(static_cast<unsigned char>(OpCodeType::OP_0));
    else
        *this << ScriptNum::serialize(n);
    return *this;
}

Script::Script() = default;
Script::Script(const_iterator begin, const_iterator end) : ScriptBase(begin, end) {}
Script::Script(const unsigned char *begin, const unsigned char *end) : ScriptBase(begin, end) {}

Script::Script(int64_t base) {
    operator<<(base);
}

Script::Script(OpCodeType base) {
    operator<<(base);
}

Script::Script(const ScriptNum &base) {
    operator<<(base);
}

bool getScriptOp(ScriptBase::const_iterator &iterator,
                 ScriptBase::const_iterator end,
                 OpCodeType &opCodeRes,
                 std::vector<unsigned char> *vchRes) {
    opCodeRes = OpCodeType::OP_INVALIDOPCODE;
    if (vchRes) vchRes->clear();
    if (iterator >= end) return false;

    // read instruction
    if (end - iterator < 1) return false;
    uint32_t opCode = *iterator++;

    // immediate operand
    if (opCode <= static_cast<uint32_t>(OpCodeType::OP_PUSHDATA4)) {
        uint32_t size = 0;
        if (opCode < static_cast<uint32_t>(OpCodeType::OP_PUSHDATA1))
            size = opCode;
        else if (opCode == static_cast<uint32_t>(OpCodeType::OP_PUSHDATA1)) {
            if (end - iterator < 1) return false;
            size = *iterator++;
        } else if (opCode == static_cast<uint32_t>(OpCodeType::OP_PUSHDATA2)) {
            if (end - iterator < 2) return false;
            size = util::encode::ReadLE16(&iterator[0]);
            iterator += 2;
        } else if (opCode == static_cast<uint32_t>(OpCodeType::OP_PUSHDATA4)) {
            if (end - iterator < 4) return false;
            size = util::encode::ReadLE32(&iterator[0]);
            iterator += 4;
        }
        if (end - iterator < 0 || (uint32_t) (end - iterator) < size)
            return false;
        if (vchRes)
            vchRes->assign(iterator, iterator + size);
        iterator += size;
    }
    opCodeRes = static_cast<OpCodeType>(opCode);
    return true;
}

bool Script::getOp(const_iterator &iterator, OpCodeType &opCode, std::vector<unsigned char> vch) const {
    return getScriptOp(iterator, this->end(), opCode, &vch);
}

bool Script::getOp(const_iterator &iterator, OpCodeType &opCode) const {
    return getScriptOp(iterator, this->end(), opCode, nullptr);
}

int32_t Script::decodeOp(OpCodeType opCode) {
    if (opCode == OpCodeType::OP_0)
        return 0;
    assert(opCode>=OpCodeType::OP_1 && opCode<=OpCodeType::OP_16);
    return static_cast<int32_t>(opCode) - static_cast<int32_t>(OpCodeType::OP_1) - 1;
}

OpCodeType Script::encodeOp(int32_t n) {
    assert(n >= 0 && n <= 16);
    if (n == 0)
        return OpCodeType::OP_0;
    return static_cast<OpCodeType>(static_cast<int32_t>(OpCodeType::OP_1) + n - 1);
}

uint32_t Script::getSigOpCount(bool accurate) const {
    uint32_t res = 0;
    auto iter = this->begin();
    OpCodeType lastOpCode = OpCodeType::OP_INVALIDOPCODE;
    while (iter < this->end()) {
        OpCodeType opCode;
        if (!this->getOp(iter, opCode))
            break;
        if (opCode == OpCodeType::OP_CHECKSIG || opCode == OpCodeType::OP_CHECKSIGVERIFY)
            res++;
        else if (opCode == OpCodeType::OP_CHECKMULTISIG || opCode == OpCodeType::OP_CHECKMULTISIGVERIFY) {
            if (accurate && lastOpCode >= OpCodeType::OP_1 && lastOpCode <= OpCodeType::OP_16)
                res += this->decodeOp(lastOpCode);
            else
                res += config::script::MAX_PUBKEYS_PER_MULTISIG;
        }
        lastOpCode = opCode;
    }
    return res;
}

uint32_t Script::getSigOpCount(const Script &scriptSig) const {
    if (!this->isPayToScriptHash())
        return this->getSigOpCount(true);
    auto iter = scriptSig.begin();
    std::vector<unsigned char> data;
    while (iter < scriptSig.end()) {
        OpCodeType opCode;
        if (!scriptSig.getOp(iter, opCode, data))
            return 0;
        if (opCode > OpCodeType::OP_16)
            return 0;
    }
    Script subScript(data.begin(), data.end());
    return subScript.getSigOpCount(true);
}

bool Script::isPayToScriptHash() const {
    return (this->size() == 23 &&
            (*this)[0] == static_cast<unsigned char>(OpCodeType::OP_HASH160) &&
            (*this)[1] == 0x14 &&
            (*this)[22] == static_cast<unsigned char>(OpCodeType::OP_EQUAL));
}

bool Script::isPayToWitnessScriptHash() const {
    return (this->size() == 34 &&
            (*this)[0] == static_cast<unsigned char>(OpCodeType::OP_0) &&
            (*this)[1] == 0x20);
}

bool Script::isWitnessProgram(int32_t &version, std::vector<unsigned char> &program) const {
    if (this->size() < 4 || this->size() > 42)
        return false;
    if ((*this)[0] != static_cast<unsigned char>(OpCodeType::OP_0) &&
        ((*this)[0] < static_cast<unsigned char>(OpCodeType::OP_1) ||
         (*this)[0] > static_cast<unsigned char>(OpCodeType::OP_16)))
        return false;
    if ((size_t) (*this)[1] + 2 == this->size()) {
        version = this->decodeOp(static_cast<OpCodeType>((*this)[0]));
        program = std::vector<unsigned char>(this->begin() + 2, this->end());
        return true;
    }
    return false;
}

bool Script::isPushOnly(const_iterator iterator) const {
    while (iterator < this->end()) {
        OpCodeType opCode;
        if (!this->getOp(iterator, opCode))
            return false;
        if (opCode > OpCodeType::OP_16)
            return false;
    }
    return true;
}

bool Script::isPushOnly() const {
    return this->isPushOnly(this->begin());
}

bool Script::hasValidOps() const {
    auto iter = this->begin();
    while (iter < this->end()) {
        OpCodeType opCode;
        std::vector<unsigned char> item;
        if (!this->getOp(iter, opCode, item) ||
            opCode > OpCodeType::OP_NOP10 ||
            item.size() > config::script::MAX_SCRIPT_ELEMENT_SIZE)
            return false;
    }
    return true;
}

bool Script::isUnspendable() const {
    return (!this->empty() && *(this->begin()) == static_cast<unsigned char>(OpCodeType::OP_RETURN)) ||
           (this->size() > config::script::MAX_SCRIPT_SIZE);
}

void Script::clear() {
    ScriptBase::clear();
    this->shrink_to_fit();
}

Script &Script::operator<<(int64_t base) {
    return this->pushInt64(base);
}

Script &Script::operator<<(OpCodeType opCode) {
    auto charCode = static_cast<unsigned char >(opCode);
    if (charCode < 0 || charCode > 0xff)
        throw std::runtime_error("Script::operator<<(): invalid opCode");
    this->insert(this->end(), charCode);
    return *this;
}

Script &Script::operator<<(const ScriptNum &base) {
    *this << base.getVch();
    return *this;
}

Script &Script::operator<<(const std::vector<unsigned char> &base) {
    if (base.size() < static_cast<unsigned char>(OpCodeType::OP_PUSHDATA1)) {
        this->insert(this->end(), static_cast<unsigned char>(base.size()));
    } else if (base.size() <= 0xff) {
        this->insert(this->end(), static_cast<unsigned char>(OpCodeType::OP_PUSHDATA1));
        this->insert(this->end(), static_cast<unsigned char>(base.size()));
    } else if (base.size() <= 0xffff) {
        this->insert(this->end(), static_cast<unsigned char>(OpCodeType::OP_PUSHDATA2));
        uint8_t data[2];
        util::encode::WriteLE16(data, base.size());
        this->insert(this->end(), data, data + sizeof(data));
    } else {
        this->insert(this->end(), static_cast<unsigned char>(OpCodeType::OP_PUSHDATA4));
        uint8_t data[4];
        util::encode::WriteLE32(data, base.size());
        this->insert(this->end(), data, data + sizeof(data));
    }
    this->insert(this->end(), base.begin(), base.end());
    return *this;
}
