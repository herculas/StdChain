#ifndef STDCHAIN_CONFIG_SCRIPT_H
#define STDCHAIN_CONFIG_SCRIPT_H

namespace config::script {

    static const uint32_t MAX_SCRIPT_ELEMENT_SIZE = 520;
    static const int32_t MAX_OPS_PER_SCRIPT = 201;
    static const int32_t MAX_PUBKEYS_PER_MULTISIG = 20;
    static const int32_t MAX_SCRIPT_SIZE = 10000;
    static const int32_t MAX_STACK_SIZE = 1000;

} // namespace config::script

#endif //STDCHAIN_CONFIG_SCRIPT_H
