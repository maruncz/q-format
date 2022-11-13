cmake_minimum_required(VERSION 3.5)

set(Q-FORMAT_SRCS
    int_types.h
    q-format.h
    )

add_library(q-format INTERFACE ${Q-FORMAT_SRCS})
target_include_directories(q-format INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
