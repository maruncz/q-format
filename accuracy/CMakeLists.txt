cmake_minimum_required(VERSION 3.11)

set(GNUPLOT_PATH "" CACHE PATH "")

find_program(GNUPLOT
    NAMES gnuplot gnuplot.exe
    HINTS ${GNUPLOT_PATH}
    REQUIRED
)

add_library(acc_common INTERFACE common.hpp)

set(ACC_SRCS_UNARY
    acc_exp.cpp
    )

set(ACC_SRCS_BINARY
    acc_mul.cpp
    acc_div.cpp
    )

set(ACC_ARGS
    1-7
    4-4
    1-15
    8-8
    1-31
    16-16
)

foreach(acc ${ACC_SRCS_UNARY})
    get_filename_component(TName ${acc} NAME_WE)
    add_executable(${TName} ${acc})
    target_link_libraries(${TName} PRIVATE qfm::qfm acc_common)
    foreach(arg ${ACC_ARGS})
        add_custom_command(
            OUTPUT ${TName}-${arg}.txt
            COMMAND ${TName} ARGS ${arg}
            DEPENDS ${TName}
        )
        add_custom_command(
            OUTPUT ${TName}-${arg}-plot.png
            COMMAND ${GNUPLOT} ARGS -e filename=\\\'${TName}-${arg}.txt\\\' -e outplot=\\\'${TName}-${arg}-plot.png\\\' ${CMAKE_CURRENT_SOURCE_DIR}/unary.gnuplot
            DEPENDS ${TName}-${arg}.txt ${CMAKE_CURRENT_SOURCE_DIR}/unary.gnuplot
        )
        list(APPEND ACC_PLOTS ${TName}-${arg}-plot.png)
    endforeach()
endforeach()

foreach(acc ${ACC_SRCS_BINARY})
    get_filename_component(TName ${acc} NAME_WE)
    add_executable(${TName} ${acc})
    target_link_libraries(${TName} PRIVATE qfm::qfm acc_common)
    foreach(arg ${ACC_ARGS})
        add_custom_command(
            OUTPUT ${TName}-${arg}.txt
            COMMAND ${TName} ARGS ${arg}
            DEPENDS ${TName}
        )
        add_custom_command(
            OUTPUT ${TName}-${arg}-plot.png
            COMMAND ${GNUPLOT} ARGS -e filename=\\\'${TName}-${arg}.txt\\\' -e outplot=\\\'${TName}-${arg}-plot.png\\\' ${CMAKE_CURRENT_SOURCE_DIR}/binary.gnuplot
            DEPENDS ${TName}-${arg}.txt ${CMAKE_CURRENT_SOURCE_DIR}/binary.gnuplot
        )
        list(APPEND ACC_PLOTS ${TName}-${arg}-plot.png)
    endforeach()
endforeach()

add_custom_target(plot-accuarancy DEPENDS ${ACC_PLOTS})
