target_sources(doubly_linked_list_lib
	PRIVATE
		doubly_linked_list.cpp
)

target_include_directories(doubly_linked_list_lib PUBLIC
	${PROJECT_SOURCE_DIR}/src
)
