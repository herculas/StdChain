#ifndef STDCHAIN_TYPE_FILE_FLAT_POS_H
#define STDCHAIN_TYPE_FILE_FLAT_POS_H

#include <cstdint>
#include <string>

class FlatFilePos {

public:
    int32_t file;
    uint32_t pos;

public:
    FlatFilePos();
    FlatFilePos(int32_t file, uint32_t pos);

    void setNull();
    [[nodiscard]] bool isNull() const;
    [[nodiscard]] std::string toString() const;

    friend bool operator==(const FlatFilePos &a, const FlatFilePos &b);
    friend bool operator!=(const FlatFilePos &a, const FlatFilePos &b);

};


#endif //STDCHAIN_TYPE_FILE_FLAT_POS_H
