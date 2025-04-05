project(shell_sort)

add_library(sort_lib "")

add_subdirectory(src)
add_subdirectory(test)

add_executable(sort_main
	main.cpp
)
target_link_libraries(sort_main sort_lib)