
#include "MatchingEngine.h"

#include <chrono>
#include <iostream>
#include <vector>
#include <random>

int main() {

    MatchingEngine engine;

    const int NUM_ORDERS = 1000000;

    std::mt19937_64 rng(42);

    std::uniform_int_distribution<int> priceDist(9900, 10100);
    std::uniform_int_distribution<int> quantityDist(1, 100);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_ORDERS; i++) {

        Order order;

        order.id = i + 1;
        order.quantity = quantityDist(rng);
        order.timestamp = i + 1;

        if (i % 2 == 0) {
            order.side = Side::BUY;
        } else {
            order.side = Side::SELL;
        }

        order.type = OrderType::LIMIT;
        order.price = priceDist(rng);

        engine.submitOrder(order);
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(
            end - start
        ).count();

    double seconds = duration / 1000000.0;

    double throughput = NUM_ORDERS / seconds;

    double averageLatency = duration / static_cast<double>(NUM_ORDERS);

    std::cout << "\n=== Matching Engine Benchmark ===\n";

    std::cout << "Orders processed: " << NUM_ORDERS << '\n';

    std::cout << "Total time: " << duration << " microseconds\n";

    std::cout << "Throughput: " << throughput << " orders/second\n";

    std::cout << "Average latency: " << averageLatency << " microseconds/order\n";

    return 0;
}
