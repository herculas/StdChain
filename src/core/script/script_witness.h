#ifndef STDCHAIN_CORE_SCRIPT_WITNESS_H
#define STDCHAIN_CORE_SCRIPT_WITNESS_H

#include <string>
#include <vector>

class ScriptWitness {

public:
    std::vector<std::vector<unsigned char>> stack;

public:
    ScriptWitness();
    void setNull();
    [[nodiscard]] bool isNull() const;
    [[nodiscard]] std::string toString() const;

};

#endif //STDCHAIN_CORE_SCRIPT_WITNESS_H
