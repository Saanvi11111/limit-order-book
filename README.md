
# Limit Order Book & Matching Engine

A single-threaded limit order book and matching engine implemented in C++20.

## Overview

This project implements a price-time priority matching engine that processes buy and sell orders using a central limit order book.

It supports limit orders, market orders, partial fills, and order cancellation.

## Features

- Limit and market order submission
- Price-time priority matching
- Partial order execution
- Order cancellation by ID
- Efficient order lookup
- Sorted bid and ask price levels
- Automated unit tests using Catch2
- Synthetic order generation and performance benchmarking

## Architecture

The order book uses three primary data structures:

- `std::map`: Maintains sorted bid and ask price levels.
- `std::list`: Maintains FIFO order queues at each price level.
- `std::unordered_map`: Maps order IDs to their locations for efficient cancellation.

## Project Structure

```text
LimitOrderBook/
├── include/
│   ├── Order.h
│   ├── OrderBook.h
│   └── MatchingEngine.h
├── src/
│   ├── OrderBook.cpp
│   ├── MatchingEngine.cpp
│   └── main.cpp
├── tests/
│   └── OrderBookTests.cpp
├── benchmarks/
│   └── Benchmark.cpp
├── CMakeLists.txt
└── README.md
```

## Build

Requirements:
- C++20 compiler
- CMake 3.20+
- Internet connection for the initial Catch2 download

Configure:

```bash
cmake -S . -B build
```

Compile:

```bash
cmake --build build -j4
```

## Run

Run the demonstration:

```bash
./build/LimitOrderBook
```

## Tests

Run automated tests:

```bash
ctest --test-dir build --output-on-failure
```

## Benchmark

Run the synthetic order benchmark:

```bash
./build/Benchmark
```

The benchmark reports total processing time, throughput, and average time per submitted order.

## Current Scope

This is an initial single-threaded implementation. Trade reporting, additional input validation, latency distribution measurements, and performance optimizations are planned.
