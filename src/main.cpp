
#include "MatchingEngine.h"

#include <iostream>

int main() {

    MatchingEngine engine;

    // Add a sell limit order
    Order sellOrder = {
        1,
        Side::SELL,
        OrderType::LIMIT,
        10500,
        100,
        1
    };

    engine.submitOrder(sellOrder);

    // Add a buy limit order that crosses the sell price
    Order buyOrder = {
        2,
        Side::BUY,
        OrderType::LIMIT,
        10500,
        60,
        2
    };

    engine.submitOrder(buyOrder);

    const OrderBook& book = engine.getOrderBook();

    std::cout << "=== Limit Order Book ===\n";

    std::cout << "Best Bid: " << book.bestBid() << '\n';
    std::cout << "Best Ask: " << book.bestAsk() << '\n';

    std::cout << "Order Book Empty: "
              << (book.empty() ? "Yes" : "No") << '\n';

    return 0;
}
