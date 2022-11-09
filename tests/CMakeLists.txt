cmake_minimum_required(VERSION 3.11)

set(TEST_SRCS
    test_addition.cpp
    test_subtraction.cpp
    test_multiplication.cpp
    test_division.cpp
    test_doubleconversion.cpp
    test_exp.cpp
    test_root.cpp
    )

add_executable(tests ${TEST_SRCS})
target_include_directories(tests INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tests PRIVATE q-format test-fw-tests-main)
