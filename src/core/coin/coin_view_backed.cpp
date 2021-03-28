#include "core/coin/coin_view_backed.h"

CoinViewBacked::CoinViewBacked(CoinView *coinView) : base{coinView} {}

bool CoinViewBacked::getCoin(const TxOutPoint &outPoint, Coin &coin) const {
    return this->base->getCoin(outPoint, coin);
}

bool CoinViewBacked::haveCoin(const TxOutPoint &outPoint) const {
    return this->base->haveCoin(outPoint);
}

Blob256 CoinViewBacked::getBestBlock() const {
    return this->base->getBestBlock();
}

std::vector<Blob256> CoinViewBacked::getHeadBlocks() const {
    return this->base->getHeadBlocks();
}

bool CoinViewBacked::batchWrite(CoinMap &coinMap, const Blob256 &hashBlock) {
    return this->base->batchWrite(coinMap, hashBlock);
}

CoinViewCursor *CoinViewBacked::cursor() const {
    return this->base->cursor();
}

size_t CoinViewBacked::estimateSize() const {
    return this->base->estimateSize();
}

void CoinViewBacked::setBackend(CoinView &coinView) {
    this->base = &coinView;
}
