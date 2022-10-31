cmake_minimum_required(VERSION 3.0.0)
project(hlibc VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(
    hlibc main.cpp
    example/list_example.cpp
    example/stack_example.cpp
    example/queue_example.cpp
    list/list.c
    stack/stack.c
    queue/queue.c
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
