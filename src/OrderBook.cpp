
#include "OrderBook.h"

#include <stdexcept>
#include <iterator>

void OrderBook::addOrder(const Order& order) {

    // Reject duplicate order IDs
    if (orderLookup_.find(order.id) != orderLookup_.end()) {
        throw std::invalid_argument("Duplicate order ID");
    }

    // Add buy order
    if (order.side == Side::BUY) {

        auto& queue = bids_[order.price];

        queue.push_back(order);

        auto position = std::prev(queue.end());

        orderLookup_[order.id] = {
            Side::BUY,
            order.price,
            position
        };
    }

    // Add sell order
    else {

        auto& queue = asks_[order.price];

        queue.push_back(order);

        auto position = std::prev(queue.end());

        orderLookup_[order.id] = {
            Side::SELL,
            order.price,
            position
        };
    }
}

bool OrderBook::cancelOrder(OrderId id) {

    auto it = orderLookup_.find(id);

    if (it == orderLookup_.end()) {
        return false;
    }

    Side side = it->second.side;
    Price price = it->second.price;

    if (side == Side::BUY) {

        auto level = bids_.find(price);

        level->second.erase(it->second.position);

        if (level->second.empty()) {
            bids_.erase(level);
        }
    }

    else {

        auto level = asks_.find(price);

        level->second.erase(it->second.position);

        if (level->second.empty()) {
            asks_.erase(level);
        }
    }

    orderLookup_.erase(it);

    return true;
}

Price OrderBook::bestBid() const {

    if (bids_.empty()) {
        return 0;
    }

    return bids_.begin()->first;
}

Price OrderBook::bestAsk() const {

    if (asks_.empty()) {
        return 0;
    }

    return asks_.begin()->first;
}

bool OrderBook::empty() const {

    return bids_.empty() && asks_.empty();
}
