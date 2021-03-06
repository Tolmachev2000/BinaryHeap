#include "pch.h"
#include <iostream>
#include <gtest/gtest.h>
#include "../BinaryHeap1/BinaryHeap.h"
#include <string>
#include <vector>
#include <set>
#include <ctime>
using std::cin;
using std::cout;
using std::vector;
using std::set;
using std::multiset;
using std::string;

TEST(ArrayTest, SmallAddTest_1) {
	Array <int> arr;
	for (int i = 1; i <= 10; i++) {
		arr.add(i);
	}
	for (int i = 0; i < 10; i++) {
		EXPECT_EQ(arr[i], i + 1);
	}
}

TEST(ArrayTest, BadPopTest_2) {
	Array <int> arr;
	ASSERT_EXIT(arr.pop_back(), ::testing::ExitedWithCode(1),
		"Can't delete from empty vector");
}

TEST(ArrayTest, AddPopTest_3) {
	Array <int> arr;
	for (int i = 1; i <= 2018; i++) {
		arr.add(i);
	}
	for (int i = 1; i <= 2018; i++) {
		arr.pop_back();
	}
	ASSERT_EXIT(arr.pop_back(), ::testing::ExitedWithCode(1),
		"Can't delete from empty vector");
}

TEST(ArrayTest, isEmptyTest_4) {
	int temp = rand();
	BinaryHeap<int> heap;
	heap.insert(temp);
	ASSERT_FALSE(heap.is_empty());
}

TEST(HeapTest, LargeStressTest_1) {
	vector <int> b;
	multiset <int> c;
	const int TEST_SIZE = 201817;

	for (int i = 0; i < TEST_SIZE; i++) {
		b.push_back(rand());
		c.insert(b[i]);
	}

	BinaryHeap <int> a(b.begin(), b.end());

	for (int i = 0; i < TEST_SIZE; i++) {
		int r1 = a.get_min(), r2 = *c.begin();
		EXPECT_EQ(r1, r2);
		a.extract_min();
		c.erase(c.begin());
	}
}

TEST(HeapTest, MassConstructorSpeedTest_2) {
	const int TEST_SIZE = 201822;
	int b[TEST_SIZE];
	for (int i = 0; i < TEST_SIZE; i++) {
		b[i] = rand();
	}
	BinaryHeap <int> a(b, b + TEST_SIZE);
}

TEST(HeapTest, ConstructorSpeedTest_3) {
	const int TEST_SIZE = 100;
	int b[TEST_SIZE];
	for (int i = 0; i < TEST_SIZE; i++) {
		b[i] = rand();
	}
	BinaryHeap <int> a(b, b + TEST_SIZE);
}

TEST(HeapTest, ExtractMinTest_4) {
	BinaryHeap <int> heap;
	heap.insert(1), heap.insert(2), heap.insert(3);
	ASSERT_EQ(heap.extract_min(), 1);
	ASSERT_EQ(heap.extract_min(), 2);
	ASSERT_EQ(heap.extract_min(), 3);
}

TEST(HeapTest, PointerChangeTest_5) {
	BinaryHeap <int> heap;
	int temp, temp1;
	for (int i = 1; i <= 10000; i++) {
		temp = rand();
		temp1 = temp + rand();
		BinaryHeap<int>::Pointer* ptr = heap.insert(temp);
		heap.change(ptr, temp1);
		ASSERT_EQ(heap.extract_min(), temp1);
	}
}

TEST(HeapTest, PointerDeleteTest_6) {
	BinaryHeap <int> heap;
	int temp;
	for (int i = 1; i <= 10000; i++) {
		temp = rand();
		BinaryHeap<int>::Pointer* ptr = heap.insert(temp);
		heap.Delete(ptr);
		ASSERT_TRUE(heap.is_empty());
	}
}

TEST(HeapTest, ChangePointerTest_7) {
	BinaryHeap<int> heap;
	BinaryHeap<int>::Pointer* ptr1 = heap.insert(10);
	BinaryHeap<int>::Pointer* ptr2 = heap.insert(20);
	BinaryHeap<int>::Pointer* ptr3 = heap.insert(30);
	heap.change(ptr1, 5);
	ASSERT_EQ(heap.get_min(), 5);
	heap.change(ptr1, 100);
	ASSERT_EQ(heap.get_min(), 20);
	heap.change(ptr3, -50);
	ASSERT_EQ(heap.get_min(), -50);
	ASSERT_EQ(heap.extract_min(), -50);
	ASSERT_EQ(heap.extract_min(), 20);
	ASSERT_EQ(heap.extract_min(), 100);
}


TEST(HeapTest, MassPointerTest_8) {
	vector<int> test;
	int temp;
	for (int i = 0; i < 100000; i++) {
		temp = rand();
		test.push_back(temp);
	}
	BinaryHeap<int> heap(test.begin(), test.end());
	sort(test.begin(), test.end());
	for (int i = 0; i < 100000; i++) {
		ASSERT_EQ(test[i], heap.extract_min());
	}
}

TEST(HeapTest, MassOptimizeTest_9) {
	multiset<int> test;
	int temp;
	BinaryHeap<int> heap;
	heap.optimize(100000, 100);
	for (int i = 0; i < 100000; i++) {
		temp = rand();
		heap.insert(temp);
		test.insert(temp);
	}
	for (int i = 0; i < 100; i++) {
		ASSERT_EQ(heap.extract_min(), *test.begin());
		test.erase(test.begin());
	}
}

TEST(HeapTest, TimeTest_10) {
	time_t start, finish;
	start = clock();
	vector <int> b;
	multiset <int> c;
	const int TEST_SIZE = 100000;
	for (int i = 0; i < TEST_SIZE; i++) {
		b.push_back(rand());
		c.insert(b[i]);
	}
	BinaryHeap <int> a(b.begin(), b.end());
	for (int i = 0; i < TEST_SIZE; i++) {
		int r1 = a.get_min(), r2 = *c.begin();
		EXPECT_EQ(r1, r2);
		a.extract_min();
		c.erase(c.begin());
	}
	finish = clock();
	ASSERT_GE(5, ((double)finish - start) / ((double)CLOCKS_PER_SEC));

}

TEST(HeapTest, ExeptionTest_11) {
	BinaryHeap <int> heap;
	ASSERT_EXIT(heap.extract_min(), ::testing::ExitedWithCode(1),
		"Can't get minimum from empty structures");
}

TEST(HeapTest, SpeedTest_12) {
	BinaryHeap <int> heap;
	time_t start = clock(), finish;
	const int TEST_SIZE = 1000000;
	for (int i = 0; i < TEST_SIZE; i++) {
		heap.insert(rand());
	}
	finish = clock();
	ASSERT_GE(1, ((double)finish - start) / ((double)CLOCKS_PER_SEC));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}