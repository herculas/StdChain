#include "core/coin/coin.h"

#include <type_traits>
#include "util/memory/memory_usage.h"

Coin::Coin() : coinbase{false}, height{0} {}
Coin::Coin(TxOut &&out, uint32_t height, bool coinbase) : out{out}, coinbase{coinbase}, height{height} {}
Coin::Coin(TxOut out, uint32_t height, bool coinbase) : out{std::move(out)}, coinbase{coinbase}, height{height} {}

void Coin::clear() {
    this->out.setNull();
    this->coinbase = false;
    this->height = 0;
}

bool Coin::isCoinbase() const {
    return this->coinbase;
}

bool Coin::isSpent() const {
    return this->out.isNull();
}

size_t Coin::dynamicMemoryUsage() const {
    return util::memory::dynamicUsage(this->out.scriptPubKey);
}
