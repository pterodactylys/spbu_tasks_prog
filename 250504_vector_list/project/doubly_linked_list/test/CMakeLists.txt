add_executable(doubly_list_test 
	test_list.cpp)
target_link_libraries(doubly_list_test
    gtest_main
    doubly_linked_list_lib
)
add_test(doubly_list_test doubly_list_test)
