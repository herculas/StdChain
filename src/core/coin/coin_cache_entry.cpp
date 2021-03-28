#include "core/coin/coin_cache_entry.h"

#include <type_traits>

CoinCacheEntry::CoinCacheEntry() : flag{0} {}
CoinCacheEntry::CoinCacheEntry(Coin &&coin) : coin{std::move(coin)}, flag{0} {}
CoinCacheEntry::CoinCacheEntry(Coin &&coin, unsigned char flag) : coin{std::move(coin)}, flag{flag} {}
