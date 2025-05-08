#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

using abc::DoublyLinkedList;

TEST(DoublyLinkedListTest, DefaultConstructor) {
	DoublyLinkedList<int> list;
	EXPECT_EQ(list.get_size(), 0);
	EXPECT_FALSE(list.has_item(1));
}

TEST(DoublyLinkedListTest, CopyConstructor) {
	DoublyLinkedList<int> list1;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	DoublyLinkedList<int> list2(list1);
	EXPECT_EQ(list2.get_size(), 3);
	EXPECT_TRUE(list2.has_item(2));
	EXPECT_TRUE(list2.has_item(1));
	EXPECT_FALSE(list2.has_item(4));
}

TEST(DoublyLinkedListTest, AssignmentOperator) {
	DoublyLinkedList<int> list1;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	DoublyLinkedList<int> list2;
	list2 = list1;
	EXPECT_EQ(list2.get_size(), 3);
	EXPECT_TRUE(list2.has_item(2));
	EXPECT_TRUE(list2.has_item(1));
	EXPECT_FALSE(list2.has_item(4));
}

TEST(DoublyLinkedListTest, GetSize) {
	DoublyLinkedList<int> list;
	for (int i = 0; i < 120; ++i) {
		list.push_back(i);
	}
	EXPECT_EQ(list.get_size(), 120);
	EXPECT_TRUE(list.has_item(119));
}

TEST(DoublyLinkedListTest, HasItem) {
	DoublyLinkedList<int> list;
	for (int i = 0; i < 120; ++i) {
		list.push_back(i);
	}
	EXPECT_TRUE(list.has_item(119));
	EXPECT_FALSE(list.has_item(120));
	EXPECT_FALSE(list.has_item(121));
}

TEST(DoublyLinkedListTest, PushBack) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	EXPECT_EQ(list.get_size(), 3);
	EXPECT_TRUE(list.has_item(2));
	EXPECT_TRUE(list.has_item(1));
	EXPECT_FALSE(list.has_item(4));
}

TEST(DoublyLinkedListTest, RemoveFirst) {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	EXPECT_TRUE(list.remove_first(2));
	EXPECT_EQ(list.get_size(), 3);
	EXPECT_FALSE(list.has_item(2));
	EXPECT_TRUE(list.has_item(1));
	EXPECT_TRUE(list.has_item(3));
	EXPECT_TRUE(list.has_item(4));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
