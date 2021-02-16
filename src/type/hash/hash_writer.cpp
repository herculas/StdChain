#include "type/hash/hash_writer.h"

#include "util/serialize/serialize.h"
#include "util/hash/common.h"

HashWriter::HashWriter(int type, int version): type(type), version(version) {}

int HashWriter::getType() const {
    return this->type;
}

int HashWriter::getVersion() const {
    return this->version;
}

void HashWriter::write(const char *pch, size_t size) {
    this->ctx.write((const unsigned char *) pch, size);
}

Blob256 HashWriter::getHash() {
    Blob256 result;
    this->ctx.finalize(result.begin());
    this->ctx.reset().write(result.begin(), SHA256::OUTPUT_SIZE).finalize(result.begin());
    return result;
}

Blob256 HashWriter::getSHA256() {
    Blob256 result;
    this->ctx.finalize(result.begin());
    return result;
}

uint64_t HashWriter::getCheapHash() {
    Blob256 result = this->getHash();
    return util::hash::ReadLE64(result.begin());
}
