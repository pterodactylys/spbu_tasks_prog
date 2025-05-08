add_executable(vector_test 
	test_vector.cpp)
target_link_libraries(vector_test
    gtest_main
    vector_lib
)
add_test(vector_test vector_test)
