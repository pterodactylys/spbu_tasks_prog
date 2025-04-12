project(long_number)

add_library(long_num_lib "")

add_subdirectory(src)

add_executable(ln_main
	main.cpp
)
target_link_libraries(ln_main long_num_lib)