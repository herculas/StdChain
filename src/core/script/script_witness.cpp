#include "core/script/script_witness.h"
#include "util/encode/string_encoding.h"

ScriptWitness::ScriptWitness() = default;

void ScriptWitness::setNull() {
    this->stack.clear();
    this->stack.shrink_to_fit();
}

bool ScriptWitness::isNull() const {
    return this->stack.empty();
}

std::string ScriptWitness::toString() const {
    std::string res = "ScriptWitness(";
    for (unsigned int i = 0; i < this->stack.size(); ++i) {
        if (i) res += ", ";
        auto s = this->stack[i];
        res += util::encode::hexStr(s);
    }
    return res + ")";
}
