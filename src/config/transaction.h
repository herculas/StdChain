#ifndef STDCHAIN_CONFIG_TRANSACTION_H
#define STDCHAIN_CONFIG_TRANSACTION_H

namespace config::transaction {

    // TxIn
    static const uint32_t SEQUENCE_FINAL = 0xffffffff;
    static const uint32_t SEQUENCE_LOCKTIME_DISABLE_FLAG = (1U << 31);
    static const uint32_t SEQUENCE_LOCKTIME_TYPE_FLAG = (1 << 22);
    static const uint32_t SEQUENCE_LOCKTIME_MASK = 0x0000ffff;
    static const uint32_t SEQUENCE_LOCKTIME_GRANULARITY = 9;

    // Tx
    static const int32_t CURRENT_VERSION = 2;
    static const int32_t SERIALIZE_TRANSACTION_NO_WITNESS = 0x40000000;
}

#endif //STDCHAIN_CONFIG_TRANSACTION_H
