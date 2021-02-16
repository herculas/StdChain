#include <iostream>

#include "core/block/block.h"

int main() {
    Block block{};
    std::cout << block.toString() << std::endl;
    return 0;
}
