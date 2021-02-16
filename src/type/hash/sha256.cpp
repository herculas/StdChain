#include "type/hash/sha256.h"

#include <cstring>
#include "util/hash/common.h"
#include "util/hash/sha.h"

SHA256::SHA256() : s{0}, bytes{0}, buf{0} {
    util::hash::initialize(s);
}

SHA256 &SHA256::write(const unsigned char *data, size_t len) {
    const unsigned char *end = data + len;
    size_t bufSize = this->bytes % 64;
    if (bufSize && bufSize + len >= 64) {
        memcpy(this->buf + bufSize, data, 64 - bufSize);
        this->bytes += 64 - bufSize;
        data += 64 - bufSize;
        util::hash::transform(this->s, this->buf, 1);
        bufSize = 0;
    }
    if (end - data >= 64) {
        size_t blocks = (end - data) / 64;
        util::hash::transform(this->s, data, blocks);
        data += 64 * blocks;
        this->bytes += 64 * blocks;
    }
    if (end > data) {
        memcpy(this->buf + bufSize, data, end - data);
        this->bytes += end - data;
    }
    return *this;
}

void SHA256::finalize(unsigned char hash[OUTPUT_SIZE]) {
    static const unsigned char pad[64] = {0x80};
    unsigned char sizeDesc[8];
    util::hash::WriteBE64(sizeDesc, bytes << 3);
    this->write(pad, 1 + ((119 - (bytes % 64)) % 64));
    this->write(sizeDesc, 8);
    util::hash::WriteBE32(hash, s[0]);
    util::hash::WriteBE32(hash + 4, s[1]);
    util::hash::WriteBE32(hash + 8, s[2]);
    util::hash::WriteBE32(hash + 12, s[3]);
    util::hash::WriteBE32(hash + 16, s[4]);
    util::hash::WriteBE32(hash + 20, s[5]);
    util::hash::WriteBE32(hash + 24, s[6]);
    util::hash::WriteBE32(hash + 28, s[7]);
}

SHA256 &SHA256::reset() {
    this->bytes = 0;
    util::hash::initialize(this->s);
    return *this;
}
