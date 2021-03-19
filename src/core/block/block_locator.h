#ifndef STDCHAIN_CORE_BLOCK_LOCATOR_H
#define STDCHAIN_CORE_BLOCK_LOCATOR_H

#include <vector>
#include "type/blob/blob_256.h"

class BlockLocator {

public:
    std::vector<Blob256> have;

public:
    BlockLocator();
    explicit BlockLocator(std::vector<Blob256> have);

    void setNull();
    [[nodiscard]] bool isNull() const;

};


#endif //STDCHAIN_CORE_BLOCK_LOCATOR_H
