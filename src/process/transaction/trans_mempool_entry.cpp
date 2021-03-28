#include "process/transaction/trans_mempool_entry.h"

#include "process/consensus/validation.h"

TxMemPoolEntry::TxMemPoolEntry(const TransactionRef &tx, const Amount &fee, int64_t time, uint32_t entryHeight,
                               bool spendsCoinbase, int64_t sigOpsCost, LockPoints lockPoints) : tx{tx}, fee{fee},
                                                        txWeight{static_cast<size_t>(process::consensus::getTransactionWeight(*tx))},
                                                        usageSize{},time{time},entryHeight{entryHeight},
                                                        spendsCoinbase{spendsCoinbase},sigOpCost{sigOpsCost},
                                                        lockPoints{lockPoints}, txHashesIndex{0} {
    this->countWithDescendants = 1;
    this->sizeWithDescendants = this->getTxSize();
    this->modFeesWithDescendants = this->fee;

    this->feeDelta = 0;

    this->countWithAncestors = 1;
    this->sizeWithAncestors = this->getTxSize();
    this->modFeesWithAncestors = this->fee;
    this->sigOpCostWithAncestors = this->sigOpCost;
}

const Transaction &TxMemPoolEntry::getTx() const {
    return *(this->tx);
}

TransactionRef TxMemPoolEntry::getSharedTx() const {
    return this->tx;
}

const Amount &TxMemPoolEntry::getFee() const {
    return this->fee;
}

size_t TxMemPoolEntry::getTxSize() const {
    // TODO
    return 0;
}

size_t TxMemPoolEntry::getTxWeight() const {
    return this->txWeight;
}

int64_t TxMemPoolEntry::getTime() const {
    return this->time;
}

uint32_t TxMemPoolEntry::getHeight() const {
    return this->entryHeight;
}

int64_t TxMemPoolEntry::getSigOpCost() const {
    return this->sigOpCost;
}

int64_t TxMemPoolEntry::getModifiedFee() const {
    return this->fee + this->feeDelta;
}

size_t TxMemPoolEntry::getDynamicMemoryUsage() const {
    return this->usageSize;
}

const LockPoints &TxMemPoolEntry::getLockPoints() const {
    return this->lockPoints;
}

uint64_t TxMemPoolEntry::getCountWithDescendants() const {
    return this->countWithDescendants;
}

uint64_t TxMemPoolEntry::getSizeWithDescendants() const {
    return this->sizeWithDescendants;
}

Amount TxMemPoolEntry::getModFeesWithDescendants() const {
    return this->modFeesWithDescendants;
}

bool TxMemPoolEntry::getSpendsCoinbase() const {
    return this->spendsCoinbase;
}

uint64_t TxMemPoolEntry::getCountWithAncestors() const {
    return this->countWithAncestors;
}

uint64_t TxMemPoolEntry::getSizeWithAncestors() const {
    return this->sizeWithAncestors;
}

Amount TxMemPoolEntry::getModFeesWithAncestors() const {
    return this->modFeesWithAncestors;
}

int64_t TxMemPoolEntry::getSigOpCostWithAncestors() const {
    return this->sigOpCostWithAncestors;
}

const TxMemPoolEntry::Parents &TxMemPoolEntry::getMemPoolParentsConst() const {
    return this->parents;
}

const TxMemPoolEntry::Children &TxMemPoolEntry::getMemPoolChildrenConst() const {
    return this->children;
}

TxMemPoolEntry::Parents &TxMemPoolEntry::getMemPoolParents() const {
    return this->parents;
}

TxMemPoolEntry::Children &TxMemPoolEntry::getMemPoolChildren() const {
    return this->children;
}

void TxMemPoolEntry::updateDescendantState(int64_t modifySize, Amount modifyFee, int64_t modifyCount) {
    this->sizeWithDescendants += modifySize;
    assert(this->sizeWithDescendants > 0);
    this->modFeesWithDescendants += modifyFee;
    this->countWithDescendants += modifyCount;
    assert(this->countWithDescendants > 0);
}

void TxMemPoolEntry::updateAncestorState(int64_t modifySize, Amount modifyFee, int64_t modifyCount, int64_t modifySigOps) {
    this->sizeWithAncestors += modifySize;
    assert(this->sizeWithAncestors > 0);
    this->modFeesWithAncestors += modifyFee;
    this->countWithAncestors += modifyCount;
    assert(this->countWithAncestors > 0);
    this->sigOpCostWithAncestors += modifySigOps;
    assert(this->sigOpCostWithAncestors >= 0);
}

void TxMemPoolEntry::updateFeeDelta(int64_t newFeeDelta) {
    this->modFeesWithDescendants += newFeeDelta - this->feeDelta;
    this->modFeesWithAncestors += newFeeDelta - this->feeDelta;
    this->feeDelta = newFeeDelta;
}

void TxMemPoolEntry::updateLockPoints(const LockPoints &newLockPoints) {
    this->lockPoints = newLockPoints;
}
