#include <iostream>
#include <sstream>
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

#include "core/block/block.h"
#include "core/transaction/trans_id_generic.h"
#include "core/chain/chain.h"

int main() {

    Block block;
    Block newBlock;
    BlockHeader header;

    block.checked = true;
    header.version = 1;
    header.time = 2;
    header.bits = 3;
    header.nonce = 4;
    block.header = header;

    MutableTransaction transaction;
    transaction.version = 114514;
    transaction.lockTime = 1919810;

    TxIn txIn(Blob256(), 114);
    TxOut txOut(514, Script());
    transaction.vin.push_back(txIn);
    transaction.vout.push_back(txOut);
    block.vTx.push_back(makeTransactionRef(transaction));

    std::ostringstream outStream;
    boost::archive::text_oarchive outArchive(outStream);
    outArchive << block;

    std::istringstream inStream(outStream.str());
    boost::archive::text_iarchive inArchive(inStream);
    inArchive >> newBlock;

    std::cout << block.toString() << std::endl;
    std::cout << newBlock.toString() << std::endl;

    return 0;
}
