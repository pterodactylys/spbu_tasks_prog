add_executable(ibusko_test 
	test_long_number.cpp)
target_link_libraries(ibusko_test
    gtest_main
    long_num_lib
)
add_test(ibusko_test ibusko_test)
