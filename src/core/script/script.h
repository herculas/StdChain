#ifndef STDCHAIN_CORE_SCRIPT_H
#define STDCHAIN_CORE_SCRIPT_H

#include <vector>
#include "boost/serialization/vector.hpp"

typedef std::vector<unsigned char> ScriptBase;
class Script : public ScriptBase {

private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &archive, unsigned int archiveVersion);

};

template<typename Archive>
void Script::serialize(Archive &archive, unsigned int archiveVersion) {
    archive & boost::serialization::base_object<ScriptBase>(*this);
}

#endif //STDCHAIN_SCRIPT_H
