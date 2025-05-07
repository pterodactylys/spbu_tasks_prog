project(vector)

add_library(vector_lib "")

add_subdirectory(src)
add_subdirectory(test)

add_executable(vector_main
	main.cpp
)
target_link_libraries(vector_main vector_lib)