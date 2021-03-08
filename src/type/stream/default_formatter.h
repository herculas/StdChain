#ifndef STDCHAIN_TYPE_STREAM_DEFAULT_FORMATTER_H
#define STDCHAIN_TYPE_STREAM_DEFAULT_FORMATTER_H

namespace util::serialize {
    template<typename Stream, typename T>
    void serialize(Stream &stream, const T &t);
}

class DefaultFormatter {

public:
    template<typename Stream, typename T>
    static void serialize(Stream &stream, const T &t) {
        util::serialize::serialize(stream, t);
    }

};

#endif //STDCHAIN_TYPE_STREAM_DEFAULT_FORMATTER_H
