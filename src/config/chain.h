#ifndef STDCHAIN_CONFIG_CHAIN_H
#define STDCHAIN_CONFIG_CHAIN_H

enum BlockStatus: uint32_t {

    BLOCK_VALID_UNKNOWN = 0,

    BLOCK_VALID_RESERVED = 1,
    BLOCK_VALID_TREE = 2,
    BLOCK_VALID_TRANSACTIONS = 3,
    BLOCK_VALID_CHAIN = 4,
    BLOCK_VALID_SCRIPTS = 5,
    BLOCK_VALID_MASK = BLOCK_VALID_RESERVED |
                       BLOCK_VALID_TREE |
                       BLOCK_VALID_TRANSACTIONS |
                       BLOCK_VALID_CHAIN |
                       BLOCK_VALID_SCRIPTS,

    BLOCK_HAVE_DATA = 8,
    BLOCK_HAVE_UNDO = 16,
    BLOCK_HAVE_MASK = BLOCK_HAVE_DATA | BLOCK_HAVE_UNDO,

    BLOCK_FAILED_VALID = 32,
    BLOCK_FAILED_CHILD = 64,
    BLOCK_FAILED_MASK = BLOCK_FAILED_VALID | BLOCK_FAILED_CHILD,

    BLOCK_OPT_WITNESS = 128,

};

#endif //STDCHAIN_CONFIG_CHAIN_H