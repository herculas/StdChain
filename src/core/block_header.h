#ifndef STDCHAIN_CORE_BLOCK_HEADER_H
#define STDCHAIN_CORE_BLOCK_HEADER_H


#include <vector>

#include "type/blob_256.h"
#include "util/encode/serialize.h"

/**
 * @par
 * collect new transactions into a block, hash them into a hash
 * tree, and scan through nonce values to make the block's hash satisfy
 * proof-of-work requirements. When they solve the proof-of-work, they
 * broadcast the block to everyone and the block is added to the blockchain.
 * The first transaction in the block is a special one that creates a new coin
 * owned by the creator of the block.
 *
 * @par
 * 節點將新交易蒐集到區塊中，並將這些交易雜湊到雜湊樹中，隨後遍歷隨機數以俾區塊之雜
 * 湊值符合工作量證明之要求。當任一節點解出工作量證明難題，即可將區塊向其他節點廣播，其
 * 他節點會將區塊插入區塊鏈中。區塊中首個交易是一個特殊交易，憑空創造新幣並獎
 * 給區塊之創造者。
 */
class BlockHeader {

public:
    // header, 區塊首部
    int32_t version;
    Blob256 hashPrevBlock;
    Blob256 hashMerkleRoot;
    uint32_t time;
    uint32_t bits;
    uint32_t nonce;

public:
    BlockHeader();
    [[nodiscard]] bool isNull() const;
    [[nodiscard]] Blob256 getHash() const;
    [[nodiscard]] int64_t getBlockTime() const;

public:
    SERIALIZE_METHODS(BlockHeader, obj) {
        READWRITE(obj.version, obj.hashPrevBlock, obj.hashMerkleRoot, obj.time, obj.bits, obj.nonce);
    }

};


#endif //STDCHAIN_CORE_BLOCK_HEADER_H
