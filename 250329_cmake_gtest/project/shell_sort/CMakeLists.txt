project(shell_sort)

set(HEADERS
	src/print.hpp
	src/sortings.hpp
)

set(SOURCES
	main.cpp
	src/print.cpp
	src/sortings.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

#add_subdirectory(test)