#include "util/hash/hasher.h"

#include <limits>
#include "util/random/generator.h"

SaltedTxOutpointHasher::SaltedTxOutpointHasher() : k0{util::random::getRand(std::numeric_limits<uint64_t>::max())},
                                                   k1{util::random::getRand(std::numeric_limits<uint64_t>::max())} {}

size_t SaltedTxOutpointHasher::operator()(const TxOutPoint &id) const noexcept {
    // TODO: SipHash
    return 0;
}
