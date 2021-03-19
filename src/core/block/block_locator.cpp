#include "core/block/block_locator.h"

#include <utility>

BlockLocator::BlockLocator() = default;
BlockLocator::BlockLocator(std::vector<Blob256> have) : have(std::move(have)) {}

void BlockLocator::setNull() {
    this->have.clear();
}

bool BlockLocator::isNull() const {
    return this->have.empty();
}
