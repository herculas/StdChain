#ifndef STDCHAIN_CORE_TRANSACTION_REFERENCE_H
#define STDCHAIN_CORE_TRANSACTION_REFERENCE_H

#include "boost/serialization/shared_ptr.hpp"
#include "core/transaction/transaction.h"

typedef std::shared_ptr<const Transaction> TransactionRef;

template<typename Tx>
static inline TransactionRef makeTransactionRef(Tx &&tx) {
    return std::make_shared<const Transaction>(std::forward<Tx>(tx));
}

#endif //STDCHAIN_CORE_TRANSACTION_REFERENCE_H
