
#pragma once

#include "OrderBook.h"

class MatchingEngine {
private:

    OrderBook book_;

    // Match incoming buy orders
    void matchBuy(Order& order);

    // Match incoming sell orders
    void matchSell(Order& order);

public:

    // Submit a new order
    void submitOrder(Order order);

    // Cancel an existing order
    bool cancelOrder(OrderId id);

    // Access the current order book
    const OrderBook& getOrderBook() const;
};
