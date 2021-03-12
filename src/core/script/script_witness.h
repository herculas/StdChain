#ifndef STDCHAIN_CORE_SCRIPT_WITNESS_H
#define STDCHAIN_CORE_SCRIPT_WITNESS_H

#include <string>
#include <vector>
#include "boost/serialization/vector.hpp"

class ScriptWitness {

public:
    std::vector<std::vector<unsigned char>> stack;

public:
    ScriptWitness();
    void setNull();
    [[nodiscard]] bool isNull() const;
    [[nodiscard]] std::string toString() const;

private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &archive, unsigned int archiveVersion);

};

template<typename Archive>
void ScriptWitness::serialize(Archive &archive, unsigned int archiveVersion) {
    archive & this->stack;
}

#endif //STDCHAIN_CORE_SCRIPT_WITNESS_H
