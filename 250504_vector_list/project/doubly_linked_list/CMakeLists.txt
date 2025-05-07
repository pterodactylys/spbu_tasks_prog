project(doubly_linked_list)

add_library(doubly_linked_list_lib "")

add_subdirectory(src)
add_subdirectory(test)

add_executable(list_main
	main.cpp
)
target_link_libraries(list_main doubly_linked_list_lib)