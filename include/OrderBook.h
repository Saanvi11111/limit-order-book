
#pragma once

#include "Order.h"

#include <map>
#include <list>
#include <unordered_map>
#include <cstdint>
#include <functional>

class MatchingEngine;

class OrderBook {

    friend class MatchingEngine;

private:

    // Buy orders: highest price first
    std::map<Price, std::list<Order>, std::greater<Price>> bids_;

    // Sell orders: lowest price first
    std::map<Price, std::list<Order>> asks_;

    // Stores the location of each order for fast cancellation
    struct OrderLocation {
        Side side;
        Price price;
        std::list<Order>::iterator position;
    };

    std::unordered_map<OrderId, OrderLocation> orderLookup_;

public:

    // Add a new order
    void addOrder(const Order& order);

    // Cancel an order using its ID
    bool cancelOrder(OrderId id);

    // Return the highest buy price
    Price bestBid() const;

    // Return the lowest sell price
    Price bestAsk() const;

    // Check whether the order book is empty
    bool empty() const;

};
