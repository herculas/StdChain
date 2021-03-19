#include "type/file/flat_file_pos.h"

#include <sstream>
#include "boost/format.hpp"

FlatFilePos::FlatFilePos(): file(-1), pos(0) {}
FlatFilePos::FlatFilePos(int32_t file, uint32_t pos): file(file), pos(pos) {}

void FlatFilePos::setNull() {
    this->file = -1;
    this->pos = 0;
}

bool FlatFilePos::isNull() const {
    return this->file == -1 && this->pos == 0;
}

std::string FlatFilePos::toString() const {
    std::stringstream stream;
    stream << boost::format("FlatFilePos(file=%i, pos=%i)")
              % this->file
              % this->pos;
    return stream.str();
}

bool operator==(const FlatFilePos &a, const FlatFilePos &b) {
    return a.file == b.file && a.pos == b.pos;
}

bool operator!=(const FlatFilePos &a, const FlatFilePos &b) {
    return !(a == b);
}
