#include "util/random/generator.h"

uint64_t util::random::getRand(uint64_t max) noexcept {
    std::random_device device;
    std::default_random_engine randomEngine(device());
    std::uniform_int_distribution<uint64_t> distribution{0, max};
    return distribution(randomEngine);
}
