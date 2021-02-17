#include "core/script/script_witness.h"

ScriptWitness::ScriptWitness() = default;

void ScriptWitness::setNull() {
    this->stack.clear();
    this->stack.shrink_to_fit();
}

bool ScriptWitness::isNull() const {
    return this->stack.empty();
}

std::string ScriptWitness::toString() const {
    // TODO
    return "std::string()";
}
