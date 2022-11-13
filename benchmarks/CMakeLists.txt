cmake_minimum_required(VERSION 3.11)

set(BENCH_SRCS
    bench_exp.cpp
    )

add_executable(benchmarks ${BENCH_SRCS})
target_include_directories(benchmarks INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(benchmarks PRIVATE q-format test-fw-benchmark-main)
