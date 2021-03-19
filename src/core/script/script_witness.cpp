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
    std::string result = "ScriptWitness(";
    for (uint32_t i = 0; i < this->stack.size(); ++i) {
        if (i) result += ", ";
        auto s = this->stack[i];
        result += util::encode::hexStr(s);
    }
    return result + ")";
}
