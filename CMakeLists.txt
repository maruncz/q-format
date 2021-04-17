cmake_minimum_required(VERSION 3.5)

project(q-format LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB qf-srcs q-format/*.h q-format/*.inl)

add_executable(q-format main.cpp ${qf-srcs})
target_include_directories(q-format PRIVATE ${CMAKE_SOURCE_DIR}/q-format)

file(GLOB test_srcs tests/*.h tests/*.cpp)
list(FILTER test_srcs EXCLUDE REGEX ".*test-generator.cpp$")

add_executable(tests ${test_srcs})
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/q-format)

add_executable(test-generator tests/test-generator.cpp)
