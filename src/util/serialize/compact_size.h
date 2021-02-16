#ifndef STDCHAIN_UTIL_SERIALIZE_COMPACT_SIZE_H
#define STDCHAIN_UTIL_SERIALIZE_COMPACT_SIZE_H

#include "util/serialize/low_level_conversion.h"

namespace util::serialize {

    template<typename Stream>
    void writeCompactSize(Stream &stream, uint64_t size) {
        if (size < 253) {
            writeData8(stream, 253);
        } else if (size <= std::numeric_limits<uint16_t>::max()) {
            writeData8(stream, 253);
            writeData16(stream, size);
        } else if (size <= std::numeric_limits<unsigned int>::max()) {
            writeData8(stream, 254);
            writeData32(stream, size);
        } else {
            writeData8(stream, 255);
            writeData64(stream, size);
        }
    }

}

#endif //STDCHAIN_UTIL_SERIALIZE_COMPACT_SIZE_H
