# ~~~
# @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
#
# Copyright (c) 2020 Ignacio Vizzo, all rights reserved
add_library(toolbox logger.cpp log_sink.cpp timer.cpp instrumentor.cpp clarg_parser.cpp matrix.cpp)

# Install headers
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        PATTERN "*.cpp"
        EXCLUDE
        PATTERN "*.txt"
        EXCLUDE)

install(TARGETS toolbox
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
