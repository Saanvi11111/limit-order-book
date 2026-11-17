
cmake_minimum_required(VERSION 3.20)

project(LimitOrderBook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

add_library(orderbook
    src/OrderBook.cpp
    src/MatchingEngine.cpp
)

target_include_directories(orderbook PUBLIC include)

add_executable(LimitOrderBook src/main.cpp)
target_link_libraries(LimitOrderBook PRIVATE orderbook)

add_executable(Benchmark benchmarks/Benchmark.cpp)
target_link_libraries(Benchmark PRIVATE orderbook)

if(BUILD_TESTING)

    include(FetchContent)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.1
    )

    FetchContent_MakeAvailable(Catch2)

    add_executable(OrderBookTests
        tests/OrderBookTests.cpp
    )

    target_link_libraries(OrderBookTests
        PRIVATE orderbook Catch2::Catch2WithMain
    )

    include(Catch)
    catch_discover_tests(OrderBookTests)

endif()
