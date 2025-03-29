cmake_minimum_required(VERSION 3.2...3.27.5)

project(project)

set(CMAKE_CXX_STANDARD 17)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(shell_sort)
include_directories(shell_sort)