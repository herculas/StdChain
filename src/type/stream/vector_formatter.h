#ifndef STDCHAIN_TYPE_STREAM_VECTOR_FORMATTER_H
#define STDCHAIN_TYPE_STREAM_VECTOR_FORMATTER_H

#include "util/serialize/compact_size.h"

template<typename Formatter>
class VectorFormatter {

public:
    template<typename Stream, typename V>
    void serialize(Stream &stream, const V &v) {
        Formatter formatter;
        util::serialize::writeCompactSize(stream, v.size());
        for (auto &elem: v)
            formatter.serialize(stream, elem);
    }

};

#endif //STDCHAIN_TYPE_STREAM_VECTOR_FORMATTER_H
