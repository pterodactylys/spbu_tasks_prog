project(tests)

set(SORT_SRC_DIR ${CMAKE_SOURCE_DIR}/shell_sort/src)
set(SORT_TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${SORT_SRC_DIR})

add_executable(sort_test
    ${SORT_TESTS_DIR}/test.cpp
    ${SORT_SRC_DIR}/sortings.cpp
)

target_link_libraries(sort_test gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(sort_test)
add_test(test sort_test)