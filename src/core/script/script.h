#ifndef STDCHAIN_CORE_SCRIPT_H
#define STDCHAIN_CORE_SCRIPT_H

#include <vector>
#include "util/serialize/serialize.h"

typedef std::vector<unsigned char> ScriptBase;

class Script : public ScriptBase {

public:
    template<typename Stream>
    void serialize(Stream &stream) const;

};

template<typename Stream>
void Script::serialize(Stream &stream) const {
    static_assert(std::is_same<const Script&, decltype(*this)>::value, "Serialize type mismatch");
    util::serialize::serializeMany(stream, (ScriptBase) *this);
}

#endif //STDCHAIN_SCRIPT_H
