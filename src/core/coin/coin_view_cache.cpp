#include "core/coin/coin_view_cache.h"

#include <stdexcept>
#include <type_traits>
#include <tuple>

CoinViewCache::CoinViewCache(CoinView *base) : CoinViewBacked(base), cachedCoinsUsage{0} {}

bool CoinViewCache::getCoin(const TxOutPoint &outPoint, Coin &coin) const {
    auto iterator = this->fetchCoin(outPoint);
    if (iterator != this->cacheCoins.end()) {
        coin = iterator->second.coin;
        return !coin.isSpent();
    }
    return false;
}

bool CoinViewCache::haveCoin(const TxOutPoint &outPoint) const {
    auto iterator = this->fetchCoin(outPoint);
    return (iterator != this->cacheCoins.end() && !iterator->second.coin.isSpent());
}

Blob256 CoinViewCache::getBestBlock() const {
    if (this->hashBlock.isNull())
        this->hashBlock = this->base->getBestBlock();
    return this->hashBlock;
}

bool CoinViewCache::batchWrite(CoinMap &coinMap, const Blob256 &hashBlockIn) {
    for (auto iterator = coinMap.begin(); iterator != coinMap.end(); iterator = coinMap.erase(iterator)) {
        if (!(iterator->second.flag & CoinCacheEntry::DIRTY)) continue;
        auto iteratorUs = this->cacheCoins.find(iterator->first);
        if (iteratorUs == this->cacheCoins.end()) {
            if (!(iterator->second.flag & CoinCacheEntry::FRESH && iterator->second.coin.isSpent())) {
                CoinCacheEntry &entry = this->cacheCoins[iterator->first];
                entry.coin = std::move(iterator->second.coin);
                this->cachedCoinsUsage += entry.coin.dynamicMemoryUsage();
                entry.flag = CoinCacheEntry::DIRTY;
                if (iterator->second.flag & CoinCacheEntry::FRESH)
                    entry.flag |= CoinCacheEntry::FRESH;
            }
        } else {
            if ((iterator->second.flag & CoinCacheEntry::FRESH) && !iteratorUs->second.coin.isSpent())
                throw std::logic_error("FRESH flag misapplied to coin that exists in parent cache.");
            if ((iteratorUs->second.flag & CoinCacheEntry::FRESH) && iterator->second.coin.isSpent()) {
                this->cachedCoinsUsage -= iteratorUs->second.coin.dynamicMemoryUsage();
                this->cacheCoins.erase(iteratorUs);
            } else {
                this->cachedCoinsUsage -= iteratorUs->second.coin.dynamicMemoryUsage();
                iteratorUs->second.coin = std::move(iterator->second.coin);
                this->cachedCoinsUsage += iteratorUs->second.coin.dynamicMemoryUsage();
                iteratorUs->second.flag |= CoinCacheEntry::DIRTY;
            }
        }
    }
    this->hashBlock = hashBlockIn;
    return true;
}

CoinViewCursor *CoinViewCache::cursor() const {
    throw std::logic_error("CoinViewCache cursor iteration not supported.");
}

void CoinViewCache::setBestBlock(const Blob256 &hashBlockIn) {
    this->hashBlock = hashBlockIn;
}

bool CoinViewCache::haveCoinInCache(const TxOutPoint &outPoint) const {
    auto iterator = this->cacheCoins.find(outPoint);
    return (iterator != this->cacheCoins.end() && !iterator->second.coin.isSpent());
}

const Coin &CoinViewCache::accessCoin(const TxOutPoint &outPoint) const {
    static const Coin coinEmpty;
    auto iterator = this->fetchCoin(outPoint);
    if (iterator == this->cacheCoins.end()) return coinEmpty;
    else return iterator->second.coin;
}

void CoinViewCache::addCoin(const TxOutPoint &outPoint, Coin &&coin, bool possibleOverwrite) {
    assert(!coin.isSpent());
    // TODO: scruptkey
}

void CoinViewCache::emplaceCoinInternalDanger(TxOutPoint &&outPoint, Coin &&coin) {
    this->cachedCoinsUsage += coin.dynamicMemoryUsage();
    this->cacheCoins.emplace(std::piecewise_construct,
                             std::forward_as_tuple(outPoint),
                             std::forward_as_tuple(std::move(coin), CoinCacheEntry::DIRTY));
}

bool CoinViewCache::spendCoin(const TxOutPoint &outPoint, Coin *moveTo) {
    auto iterator = this->fetchCoin(outPoint);
    if (iterator == this->cacheCoins.end())
        return false;
    this->cachedCoinsUsage -= iterator->second.coin.dynamicMemoryUsage();
    if (moveTo)
        *moveTo = std::move(iterator->second.coin);
    if (iterator->second.flag & CoinCacheEntry::FRESH) {
        this->cacheCoins.erase(iterator);
    }
    else {
        iterator->second.flag |= CoinCacheEntry::DIRTY;
        iterator->second.coin.clear();
    }
    return true;
}

bool CoinViewCache::flush() {
    bool ok = this->base->batchWrite(this->cacheCoins, this->hashBlock);
    this->cacheCoins.clear();
    this->cachedCoinsUsage = 0;
    return ok;
}

void CoinViewCache::unCache(const TxOutPoint &outPoint) {
    auto iterator = this->cacheCoins.find(outPoint);
    if (iterator != this->cacheCoins.end() && iterator->second.flag == 0) {
        this->cachedCoinsUsage -= iterator->second.coin.dynamicMemoryUsage();
        this->cacheCoins.erase(iterator);
    }
}

uint32_t CoinViewCache::getCacheSize() const {
    return this->cacheCoins.size();
}

size_t CoinViewCache::dynamicMemoryUsage() const {
    // TODO: memusage
    return 0;
}

bool CoinViewCache::haveInputs(const Transaction &transaction) const {
    if (!transaction.isCoinbase())
        for (const auto & txIn : transaction.vin)
            if (!this->haveCoin(txIn.prevOut))
                return false;
    return true;
}

void CoinViewCache::reallocateCache() {
    assert(this->cacheCoins.empty());
    this->cacheCoins.~CoinMap();
    new(&this->cacheCoins) CoinMap();
}

CoinMap::iterator CoinViewCache::fetchCoin(const TxOutPoint &outPoint) const {
    auto iterator = this->cacheCoins.find(outPoint);
    if (iterator != this->cacheCoins.end()) return iterator;

    Coin temp;
    if (!this->base->getCoin(outPoint, temp)) return this->cacheCoins.end();

    auto res = this->cacheCoins.emplace(std::piecewise_construct,
                                        std::forward_as_tuple(outPoint),
                                        std::forward_as_tuple(std::move(temp))).first;
    if (res->second.coin.isSpent()) res->second.flag = CoinCacheEntry::FRESH;
    this->cachedCoinsUsage += res->second.coin.dynamicMemoryUsage();
    return res;
}
