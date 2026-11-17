
#pragma once

#include <cstdint>

enum class Side {
    BUY,
    SELL
};

enum class OrderType {
    LIMIT,
    MARKET
};

using OrderId = uint64_t;
using Price = int64_t;
using Quantity = uint64_t;

struct Order {
    OrderId id;
    Side side;
    OrderType type;
    Price price;
    Quantity quantity;
    uint64_t timestamp;
};
