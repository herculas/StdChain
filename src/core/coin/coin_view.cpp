#include "core/coin/coin_view.h"

CoinView::~CoinView() = default;

bool CoinView::getCoin(const TxOutPoint &outPoint, Coin &coin) const {
    return false;
}

bool CoinView::haveCoin(const TxOutPoint &outPoint) const {
    Coin coin;
    return this->getCoin(outPoint, coin);
}

Blob256 CoinView::getBestBlock() const {
    return Blob256();
}

std::vector<Blob256> CoinView::getHeadBlocks() const {
    return std::vector<Blob256>();
}

bool CoinView::batchWrite(CoinMap &coinMap, const Blob256 &hashBlock) {
    return false;
}

CoinViewCursor *CoinView::cursor() const {
    return nullptr;
}

size_t CoinView::estimateSize() const {
    return 0;
}
