cmake_minimum_required(VERSION 3.0.0)
project(hlib VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(
    hlib main.cpp
    example/list_example.cpp
    list/list.c
    list/stack.c
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
