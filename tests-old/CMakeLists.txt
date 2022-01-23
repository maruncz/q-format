cmake_minimum_required(VERSION 3.5)

set(TEST_SRCS
    test_addition.cpp
    test_addition.h
    test_division.cpp
    test_division.h
    test_doubleconversion.cpp
    test_doubleconversion.h
    test_exp.cpp
    test_exp.h
    test_limits.h
    test_limits_max16.cpp
    test_limits_max32.cpp
    test_limits_max8.cpp
    test_limits_min16.cpp
    test_limits_min32.cpp
    test_limits_min8.cpp
    test_misc.cpp
    test_misc.h
    test_multiplications.cpp
    test_multiplications.h
    test_root.cpp
    test_root.h
    tests.cpp
    test_separ.cpp
    test_separ.h
    test_subtraction.cpp
    test_subtraction.h
    )

add_executable(tests-old ${TEST_SRCS})
target_include_directories(tests-old INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tests-old PRIVATE q-format)
