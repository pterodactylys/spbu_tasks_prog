target_sources(sort_lib
	PRIVATE
		print.cpp
		sortings.cpp
)

target_include_directories(sort_lib PUBLIC
	${PROJECT_SOURCE_DIR}/src
)
