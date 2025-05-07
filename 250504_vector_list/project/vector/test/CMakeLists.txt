add_executable(ibusko_test 
	test_vector.cpp)
target_link_libraries(ibusko_test
    gtest_main
    vector_lib
)
add_test(ibusko_test ibusko_test)
