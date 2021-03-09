#include <iostream>
#include <sstream>

#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"

#include "core/block/block.h"

int main() {

    BlockHeader header;
    header.version = 1;
    header.time = 2;
    header.bits = 3;
    header.nonce = 4;

    header.hashMerkleRoot.setHex("1122334455667788990000998877665544332211");

    std::cout << header.hashMerkleRoot.getHex() << std::endl;

//    std::ofstream ofstream("block_header_stream");
//    boost::archive::text_oarchive oarchive(ofstream);
//    oarchive << header;
//
    BlockHeader newHeader;

    std::ostringstream outStream;
    boost::archive::text_oarchive outArchive(outStream);
    outArchive << header;

    std::string content = outStream.str();

    std::istringstream inStream(content);
    boost::archive::text_iarchive inArchive(inStream);
    inArchive >> newHeader;

    std::cout << newHeader.version << newHeader.time << newHeader.bits << newHeader.nonce << std::endl;
    std::cout << newHeader.hashMerkleRoot.getHex() << std::endl;

    return 0;
}
