#ifndef STDCHAIN_UTIL_RANDOM_GENERATOR_H
#define STDCHAIN_UTIL_RANDOM_GENERATOR_H

#include <random>

namespace util::random {
    uint64_t getRand(uint64_t max) noexcept;

} // namespace util::random

#endif //STDCHAIN_UTIL_RANDOM_GENERATOR_H
