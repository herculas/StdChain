#include "core/coin/coin_view_cursor.h"

CoinViewCursor::CoinViewCursor(const Blob256 &hashBlock) : hashBlock{hashBlock} {}
CoinViewCursor::~CoinViewCursor() = default;

const Blob256 &CoinViewCursor::getBestBlock() const {
    return this->hashBlock;
}