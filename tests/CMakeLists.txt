cmake_minimum_required(VERSION 3.11)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(TEST_SRCS
    test_addition.cpp
    test_subtraction.cpp
    test_multiplication.cpp
    test_division.cpp
    )

add_executable(tests ${TEST_SRCS})
target_include_directories(tests INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tests PRIVATE q-format gtest_main)
