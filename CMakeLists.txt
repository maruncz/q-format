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
option(BUILD_BENCHMARKS FALSE)
option(TEST_FW_LOCAL FALSE)
set(TEST_FW_DIR "" CACHE PATH "")

if(${BUILD_TESTS} OR ${BUILD_BENCHMARKS})
    include(FetchContent)
    if(${TEST_FW_LOCAL})
        FetchContent_Declare(
          test-fw
          SOURCE_DIR ${TEST_FW_DIR}
        )
    else()
        FetchContent_Declare(
          test-fw
          GIT_REPOSITORY git@gitlab.com:xbarin08/test-framework.git
          GIT_TAG develop
        )
    endif()
    FetchContent_MakeAvailable(test-fw)
endif()

if(${BUILD_TESTS})
    add_subdirectory(tests)
endif()

if(${BUILD_BENCHMARKS})
    add_subdirectory(benchmarks)
endif()
