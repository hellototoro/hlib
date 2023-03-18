cmake_minimum_required(VERSION 3.0.0)
project(hlibc VERSION 0.1.0)

include(CTest)
enable_testing()

SET(CMAKE_C_FLAGS "-O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS "-O0 -Wall -g2 -ggdb")

add_executable(
    hlibc main.c
    example/list_example.c
    example/stack_example.c
    example/queue_example.c
    list/hlist.c
    stack/hstack.c
    queue/hqueue.c
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
