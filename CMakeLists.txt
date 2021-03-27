cmake_minimum_required(VERSION 3.5)

project(q-format LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(tests/tests.cmake)
file(GLOB qf-srcs q-format/*.h)

add_executable(q-format main.cpp ${qf-srcs})
target_include_directories(q-format PRIVATE ${CMAKE_SOURCE_DIR}/q-format)
