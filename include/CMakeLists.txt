cmake_minimum_required(VERSION 3.5)

set(QFM_SRCS
    qfm/qfm.hpp
    qfm/detail/int_types.h
    qfm/detail/q_impl.hpp
    )

add_library(qfm INTERFACE ${QFM_SRCS})
target_include_directories(qfm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_library(qfm::qfm ALIAS qfm)
