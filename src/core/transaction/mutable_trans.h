#ifndef STDCHAIN_CORE_TRANSACTION_MUTABLE_H
#define STDCHAIN_CORE_TRANSACTION_MUTABLE_H

#include <vector>
#include "core/transaction/trans_in.h"
#include "core/transaction/trans_out.h"

class MutableTransaction {

public:
    int32_t version;
    uint32_t lockTime;
    std::vector<TxIn> vin;
    std::vector<TxOut> vout;

};


#endif //STDCHAIN_CORE_TRANSACTION_MUTABLE_H
