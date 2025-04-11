target_sources(long_num_lib
	PRIVATE
		long_number.cpp
)

target_include_directories(long_num_lib PUBLIC
	${PROJECT_SOURCE_DIR}/src
)
