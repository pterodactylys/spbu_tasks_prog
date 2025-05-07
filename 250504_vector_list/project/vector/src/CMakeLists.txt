target_sources(vector_lib
	PRIVATE
		vector.cpp
)

target_include_directories(vector_lib PUBLIC
	${PROJECT_SOURCE_DIR}/src
)
