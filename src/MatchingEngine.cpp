
#include "MatchingEngine.h"
#include <algorithm>

void MatchingEngine::matchBuy(Order& order) {

    while (order.quantity > 0 && !book_.asks_.empty()) {

        auto level = book_.asks_.begin();

        if (order.type == OrderType::LIMIT &&
            level->first > order.price) {
            break;
        }

        auto& queue = level->second;
        Order& restingOrder = queue.front();

        Quantity traded = std::min(
            order.quantity,
            restingOrder.quantity
        );

        order.quantity -= traded;
        restingOrder.quantity -= traded;

        if (restingOrder.quantity == 0) {
            book_.orderLookup_.erase(restingOrder.id);
            queue.pop_front();
        }

        if (queue.empty()) {
            book_.asks_.erase(level);
        }
    }
}

void MatchingEngine::matchSell(Order& order) {

    while (order.quantity > 0 && !book_.bids_.empty()) {

        auto level = book_.bids_.begin();

        if (order.type == OrderType::LIMIT &&
            level->first < order.price) {
            break;
        }

        auto& queue = level->second;
        Order& restingOrder = queue.front();

        Quantity traded = std::min(
            order.quantity,
            restingOrder.quantity
        );

        order.quantity -= traded;
        restingOrder.quantity -= traded;

        if (restingOrder.quantity == 0) {
            book_.orderLookup_.erase(restingOrder.id);
            queue.pop_front();
        }

        if (queue.empty()) {
            book_.bids_.erase(level);
        }
    }
}

void MatchingEngine::submitOrder(Order order) {

    if (order.quantity == 0) {
        return;
    }

    if (order.side == Side::BUY) {
        matchBuy(order);
    } else {
        matchSell(order);
    }

    if (order.type == OrderType::LIMIT &&
        order.quantity > 0) {
        book_.addOrder(order);
    }
}

bool MatchingEngine::cancelOrder(OrderId id) {
    return book_.cancelOrder(id);
}

const OrderBook& MatchingEngine::getOrderBook() const {
    return book_;
}
