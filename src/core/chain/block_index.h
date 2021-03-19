#ifndef STDCHAIN_CORE_CHAIN_BLOCK_INDEX_H
#define STDCHAIN_CORE_CHAIN_BLOCK_INDEX_H

#include <string>

#include "config/chain.h"
#include "core/block/block_header.h"
#include "type/arith/uint_256.h"
#include "type/file/flat_file_pos.h"
#include "type/blob/blob_256.h"

class BlockIndex {

public:
    const Blob256 *hashBlock;
    BlockIndex *prevBlock;
    BlockIndex *skipBlock;
    int32_t height;
    int32_t file;
    uint32_t dataPos;
    uint32_t undoPos;

    Uint256 chainWork;

    uint32_t tx;
    uint32_t chainTx;
    uint32_t status;

    int32_t version;
    Blob256 hashMerkleRoot;
    uint32_t time;
    uint32_t bits;
    uint32_t nonce;

    int32_t sequenceId;
    uint32_t timeMax;

public:
    BlockIndex();
    explicit BlockIndex(const BlockHeader &header);

    [[nodiscard]] FlatFilePos getBlockPos() const;
    [[nodiscard]] FlatFilePos getUndoPos() const;

    [[nodiscard]] BlockHeader getBlockHeader() const;
    [[nodiscard]] Blob256 getBlockHash() const;

    [[nodiscard]] bool isValid(BlockStatus upTo = BlockStatus::BLOCK_VALID_TRANSACTIONS) const;
    [[nodiscard]] bool haveTransactionsDownloaded() const;
    bool raiseValidity(BlockStatus upTo);

    [[nodiscard]] int64_t getBlockTime() const;
    [[nodiscard]] int64_t getBlockTimeMax() const;
    [[nodiscard]] int64_t getMedianTimePast() const;

    void buildSkip();

    BlockIndex *getAncestor(int32_t ancHeight);
    [[nodiscard]] const BlockIndex *getAncestor(int32_t ancHeight) const;

    [[nodiscard]] std::string toString() const;
};

#endif //STDCHAIN_CORE_CHAIN_BLOCK_INDEX_H
