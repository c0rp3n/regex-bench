cmake_minimum_required(VERSION 3.10)

project(RegexBench
    VERSION 1.0.0
    DESCRIPTION "A C++ STD vs Boost Regex Benchmark."
    LANGUAGES CXX
)

find_package(benchmark REQUIRED)
find_package(Boost COMPONENTS regex REQUIRED)

add_executable(regex_bench
    src/bench.cpp
)

set_target_properties(regex_bench
    PROPERTIES 
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)

target_link_libraries(regex_bench PUBLIC
    benchmark::benchmark
    ${Boost_LIBRARIES}
)
