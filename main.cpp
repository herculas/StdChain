#include <iostream>
#include "core/block/block.h"

int main() {

    BlockHeader header;
    header.version = 1;
    header.nonce = 1;
    header.bits = 1;
    header.time = 1;
    header.hashMerkleRoot.setHex("0");
    header.hashPrevBlock.setHex("0");

    std::cout << header.getHash().getHex() << std::endl;

    Block block(header);
    std::cout << block.toString() << std::endl;

    return 0;
}
