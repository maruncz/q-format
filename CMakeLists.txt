cmake_minimum_required(VERSION 3.5)

project(q-format LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

option(BUILD_DEV_BINARY FALSE)
if(${BUILD_DEV_BINARY})
    add_executable(q-format-scratch main.cpp)
    target_link_libraries(q-format-scratch PRIVATE q-format)
endif()

option(BUILD_TESTS FALSE)
if(${BUILD_TESTS})
    add_subdirectory(tests)
endif()

option(BUILD_OLD_TESTS FALSE)
if(${BUILD_OLD_TESTS})
    add_subdirectory(tests-old)
endif()
