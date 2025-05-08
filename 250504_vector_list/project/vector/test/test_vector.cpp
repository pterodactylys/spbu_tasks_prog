#include <gtest/gtest.h>

#include "vector.hpp"

using abc::Vector;

// Тесты
TEST(VectorTest, DefaultConstructor) {
	Vector<int> vec;
	EXPECT_EQ(vec.get_size(), 0);
}

TEST(VectorTest, PushBack) {
	Vector<int> vec;
	for (int i = 0; i < 5; ++i) {
		vec.push_back(i);
	}
	EXPECT_EQ(vec.get_size(), 5);
	EXPECT_TRUE(vec.has_item(0));
	EXPECT_TRUE(vec.has_item(4));
	EXPECT_FALSE(vec.has_item(5));
}

TEST(VectorTest, Insert) {
	Vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.insert(1, 3);
	EXPECT_EQ(vec.get_size(), 3);
	EXPECT_TRUE(vec.has_item(2));
	EXPECT_FALSE(vec.has_item(4));
}

TEST(VectorTest, RemoveFirst) {
	Vector<int> vec;
	vec.push_back(1234512);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	EXPECT_EQ(vec.get_size(), 4);
	EXPECT_TRUE(vec.remove_first(1234512));
	EXPECT_EQ(vec.get_size(), 3);
	EXPECT_FALSE(vec.has_item(1234512));
}

TEST(VectorTest, CopyConstructor) {
	Vector<int> vec;
	vec.push_back(1654);
	vec.push_back(2123);
	vec.push_back(3432);
	Vector<int> vec2(vec);
	EXPECT_EQ(vec2.get_size(), 3);
	EXPECT_TRUE(vec2.has_item(1654));
	EXPECT_TRUE(vec2.has_item(2123));
	EXPECT_FALSE(vec2.has_item(4));
}

TEST(VectorTest, AssignmentOperator) {
	Vector<int> vec;
	vec.push_back(1654);
	vec.push_back(2123);
	vec.push_back(3432);
	Vector<int> vec2(vec);
	EXPECT_EQ(vec2.get_size(), 3);
	EXPECT_TRUE(vec2.has_item(1654));
	EXPECT_TRUE(vec2.has_item(2123));
	EXPECT_FALSE(vec2.has_item(4));
}

TEST(VectorTest, InvalidInsert) {
	Vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	EXPECT_FALSE(vec.insert(3, 3));
	EXPECT_EQ(vec.get_size(), 2);
}


	

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
