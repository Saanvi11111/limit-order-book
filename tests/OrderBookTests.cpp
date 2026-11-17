
#include "MatchingEngine.h"

#include <catch2/catch_test_macros.hpp>
#include <stdexcept>

TEST_CASE("Limit orders are added to the book") {

    MatchingEngine engine;

    Order sell = {
        1, Side::SELL, OrderType::LIMIT, 10500, 100, 1
    };

    engine.submitOrder(sell);

    REQUIRE(engine.getOrderBook().bestAsk() == 10500);
    REQUIRE(engine.getOrderBook().bestBid() == 0);
    REQUIRE_FALSE(engine.getOrderBook().empty());
}

TEST_CASE("Crossing limit orders are matched") {

    MatchingEngine engine;

    Order sell = {
        1, Side::SELL, OrderType::LIMIT, 10500, 100, 1
    };

    Order buy = {
        2, Side::BUY, OrderType::LIMIT, 10500, 60, 2
    };

    engine.submitOrder(sell);
    engine.submitOrder(buy);

    REQUIRE(engine.getOrderBook().bestAsk() == 10500);

    // The remaining 40 shares can still be matched.
    Order secondBuy = {
        3, Side::BUY, OrderType::MARKET, 0, 40, 3
    };

    engine.submitOrder(secondBuy);

    REQUIRE(engine.getOrderBook().empty());
}

TEST_CASE("Price priority is respected") {

    MatchingEngine engine;

    Order expensiveSell = {
        1, Side::SELL, OrderType::LIMIT, 10200, 10, 1
    };

    Order cheapSell = {
        2, Side::SELL, OrderType::LIMIT, 10100, 10, 2
    };

    engine.submitOrder(expensiveSell);
    engine.submitOrder(cheapSell);

    Order buy = {
        3, Side::BUY, OrderType::MARKET, 0, 10, 3
    };

    engine.submitOrder(buy);

    REQUIRE(engine.getOrderBook().bestAsk() == 10200);
}

TEST_CASE("Time priority is respected at the same price") {

    MatchingEngine engine;

    Order first = {
        1, Side::SELL, OrderType::LIMIT, 10500, 10, 1
    };

    Order second = {
        2, Side::SELL, OrderType::LIMIT, 10500, 10, 2
    };

    engine.submitOrder(first);
    engine.submitOrder(second);

    Order buy = {
        3, Side::BUY, OrderType::MARKET, 0, 10, 3
    };

    engine.submitOrder(buy);

    // First order was filled.
    REQUIRE_FALSE(engine.cancelOrder(1));

    // Second order is still resting.
    REQUIRE(engine.cancelOrder(2));
}

TEST_CASE("Orders can be cancelled") {

    MatchingEngine engine;

    Order buy = {
        1, Side::BUY, OrderType::LIMIT, 10000, 50, 1
    };

    engine.submitOrder(buy);

    REQUIRE(engine.cancelOrder(1));
    REQUIRE_FALSE(engine.cancelOrder(1));
    REQUIRE(engine.getOrderBook().empty());
}

TEST_CASE("Unfilled market orders are discarded") {

    MatchingEngine engine;

    Order buy = {
        1, Side::BUY, OrderType::MARKET, 0, 100, 1
    };

    engine.submitOrder(buy);

    REQUIRE(engine.getOrderBook().empty());
}

TEST_CASE("Non-crossing limit orders remain in the book") {

    MatchingEngine engine;

    Order sell = {
        1, Side::SELL, OrderType::LIMIT, 10500, 100, 1
    };

    Order buy = {
        2, Side::BUY, OrderType::LIMIT, 10400, 100, 2
    };

    engine.submitOrder(sell);
    engine.submitOrder(buy);

    REQUIRE(engine.getOrderBook().bestBid() == 10400);
    REQUIRE(engine.getOrderBook().bestAsk() == 10500);
}

TEST_CASE("Duplicate order IDs are rejected") {

    OrderBook book;

    Order first = {
        1, Side::BUY, OrderType::LIMIT, 10000, 50, 1
    };

    Order duplicate = {
        1, Side::BUY, OrderType::LIMIT, 10100, 50, 2
    };

    book.addOrder(first);

    REQUIRE_THROWS_AS(
        book.addOrder(duplicate),
        std::invalid_argument
    );
}
