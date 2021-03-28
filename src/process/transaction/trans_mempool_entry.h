#ifndef STDCHAIN_PROCESS_TRANSACTION_MEMPOOL_ENTRY_H
#define STDCHAIN_PROCESS_TRANSACTION_MEMPOOL_ENTRY_H

#include <set>
#include <type_traits>
#include "core/transaction/trans_ref.h"
#include "process/transaction/lock_point.h"
#include "process/transaction/compare_Iterator_by_hash.h"
#include "type/basic/amount.h"

/**
 * @paragraph
 * TxMemPoolEntry stores data about the corresponding transaction, as well as
 * data about all in-mempool transactions that depends on the transaction
 * ("descendant" transactions).
 *
 * @paragraph
 * When a new entry is added into the mempool, we update the descendant state
 * (countWithDescendants, sizeWithDescendants, modFeesWithDescendants) for all
 * ancestors of the newly added transaction.
 */
class TxMemPoolEntry {

public:
    typedef std::reference_wrapper<const TxMemPoolEntry> TxMempoolEntryRef;
    typedef std::set<TxMempoolEntryRef, CompareIteratorByHash> Parents;
    typedef std::set<TxMempoolEntryRef, CompareIteratorByHash> Children;

private:
    const TransactionRef tx;

    mutable Parents parents;
    mutable Children children;

    const Amount fee;
    const size_t txWeight;
    const size_t usageSize;
    const int64_t time;
    const uint32_t entryHeight;
    const bool spendsCoinbase;
    const int64_t sigOpCost;

    int64_t feeDelta;
    LockPoints lockPoints;

    uint64_t countWithDescendants;
    uint64_t sizeWithDescendants;
    Amount modFeesWithDescendants;

    uint64_t countWithAncestors;
    uint64_t sizeWithAncestors;
    Amount modFeesWithAncestors;
    int64_t sigOpCostWithAncestors;

public:
    mutable size_t txHashesIndex;
    // TODO: Epoch::Marker epochMarker;

public:
    TxMemPoolEntry(const TransactionRef &tx, const Amount &fee, int64_t time, uint32_t entryHeight,
                   bool spendsCoinbase, int64_t sigOpsCost, LockPoints lockPoints);

    const Transaction &getTx() const;

    TransactionRef getSharedTx() const;
    const Amount &getFee() const;
    size_t getTxSize() const;
    size_t getTxWeight() const;
    int64_t getTime() const;
    uint32_t getHeight() const;
    int64_t getSigOpCost() const;
    int64_t getModifiedFee() const;
    size_t getDynamicMemoryUsage() const;
    const LockPoints &getLockPoints() const;

    uint64_t getCountWithDescendants() const;
    uint64_t getSizeWithDescendants() const;
    Amount getModFeesWithDescendants() const;
    
    bool getSpendsCoinbase() const;

    uint64_t getCountWithAncestors() const;
    uint64_t getSizeWithAncestors() const;
    Amount getModFeesWithAncestors() const;
    int64_t getSigOpCostWithAncestors() const;

    const Parents &getMemPoolParentsConst() const;
    const Children &getMemPoolChildrenConst() const;
    Parents &getMemPoolParents() const;
    Children &getMemPoolChildren() const;

    void updateDescendantState(int64_t modifySize, Amount modifyFee, int64_t modifyCount);
    void updateAncestorState(int64_t modifySize, Amount modifyFee, int64_t modifyCount, int64_t modifySigOps);
    void updateFeeDelta(int64_t newFeeDelta);
    void updateLockPoints(const LockPoints &newLockPoints);

};

#endif //STDCHAIN_PROCESS_TRANSACTION_MEMPOOL_ENTRY_H
