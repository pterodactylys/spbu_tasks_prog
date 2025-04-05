add_executable(sort_test
	test.cpp
)

target_link_libraries(sort_test gtest gtest_main sort_lib)

add_test(sort_test sort_test)
