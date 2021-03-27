add_definitions(-DGTEST_LANGUAGE_CXX20)
find_package(Threads REQUIRED)

set(GOOGLETEST_DIR "" CACHE PATH "gtest dir")

if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

file(GLOB test_srcs tests/*.h tests/*.cpp)

#list(REMOVE_ITEM test_srcs ${CMAKE_CURRENT_DIR}/tests/test-generator.cpp)

list(FILTER test_srcs EXCLUDE REGEX ".*test-generator.cpp$")

add_library(gtest STATIC ${GTestFiles})
target_include_directories(gtest PRIVATE ${GTestIncludes})
target_link_libraries(gtest PRIVATE Threads::Threads)

add_executable(tests ${test_srcs})
add_dependencies(tests gtest)
target_include_directories(tests PRIVATE ${GTestIncludes} ${CMAKE_SOURCE_DIR}/q-format)
target_link_libraries(tests PRIVATE Threads::Threads gtest)

#add_test(NAME test COMMAND test)

add_executable(test-generator tests/test-generator.cpp)
