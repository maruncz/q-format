cmake_minimum_required(VERSION 3.5)

project(q-format LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(tests/CMakeLists.txt)

add_executable(q-format main.cpp q-format.h)
