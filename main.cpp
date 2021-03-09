#include <iostream>
#include <sstream>
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

#include "core/block/block.h"

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

    std::ostringstream outStream;
    boost::archive::text_oarchive outArchive(outStream);
    outArchive << block;

    std::istringstream inStream(outStream.str());
    boost::archive::text_iarchive inArchive(inStream);
    inArchive >> newBlock;

    std::cout << newBlock.checked << std::endl;
    std::cout << newBlock.header.version << newBlock.header.time << newBlock.header.bits << newBlock.header.nonce
              << std::endl;

    return 0;
}
