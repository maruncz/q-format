file(GLOB test_srcs tests/*.h tests/*.cpp)
list(FILTER test_srcs EXCLUDE REGEX ".*test-generator.cpp$")

add_executable(tests ${test_srcs})
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/q-format)

add_executable(test-generator tests/test-generator.cpp)
