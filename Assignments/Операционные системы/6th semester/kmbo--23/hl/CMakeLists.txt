cmake_minimum_required(VERSION 3.10)
project(hl C)

set(COMMON_SOURCES
    strlcat.c
    common.c
)

add_executable(hlgenerator
    hlgenerator.c
    ${COMMON_SOURCES}
)

add_executable(hldetector
    hldetector.c
    ${COMMON_SOURCES}
    hlparser.c
)
