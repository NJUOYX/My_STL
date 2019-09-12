#include "pch.h"
#include"List.h"
#include<vector>
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
	srand(0);
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

class ArraySizeTest :public testing::TestWithParam<int> {

};
INSTANTIATE_TEST_CASE_P(size_return, ArraySizeTest, testing::Range(0, 100));
class ErrorArraySize :public testing::TestWithParam<int> {

};
INSTANTIATE_TEST_CASE_P(size_return, ErrorArraySize, testing::Range(-100, -1));
TEST_P(ArraySizeTest, dynamic_array_build) {
	int n = GetParam();
	mylib::DynamicArray<int> da(n);
	EXPECT_EQ(da.size, da.get_size());
}
TEST_P(ArraySizeTest, size_return) {
	int n = GetParam();
	mylib::DynamicArray<int>da;
	da.resize(n);
	EXPECT_EQ(da.get_size(), n);
}
TEST_P(ErrorArraySize, size_param_erro) {
	int n = GetParam();
	EXPECT_ANY_THROW(mylib::DynamicArray<int>da(n));
}

TEST_P(ArraySizeTest, resize_error) {
	int n = GetParam();
	mylib::DynamicArray<int>da(n+1);
	EXPECT_FALSE(da.resize(n));
}
TEST_P(ArraySizeTest, SEQLIST_size_equal_getsize) {
	int n = GetParam();
	mylib::SeqList<int>da(n);
	EXPECT_EQ(da.Size(), da._array.get_size());
}

TEST_P(ArraySizeTest, SEQ_LIST_build_size) {
	int n = GetParam();
	mylib::SeqList<int>sa(n);
	EXPECT_EQ(sa.Size(), n);
}
TEST_P(ErrorArraySize, SEQ_LIST_build_size_erro) {
	int n = GetParam();
	EXPECT_ANY_THROW(mylib::SeqList<int>sa(n));
}
TEST(NormalTest, SEQ_LIST_input_build) {
	mylib::SeqList<int>sa{1,2,3,4,5,6,7,8,9,10};
	EXPECT_EQ(sa.Length(), 10);
	EXPECT_EQ(sa.Size(), 10);
	mylib::SeqList<int>sb({ 1,2,3,4,5 }, 10);
	EXPECT_EQ(sb.Length(), 5);
	EXPECT_EQ(sb.Size(), 10);
}

TEST(NormalTest, SEQ_LIST_search) {
	mylib::SeqList<int>sa{ 1,2,3,4,5,6,7,8,9,10 };
	for (auto i = 1; i <= 10; ++i) {
		EXPECT_EQ(sa.Search(i), i);
	}
	EXPECT_EQ(sa.Search(21), SEARCH_FAILED);
}

TEST(NormalTest, SEQ_LIST_Locate) {
	mylib::SeqList<int>sa{ -1,-2,-3,4,5,6,7,8,9,10 };
	for (auto i = 1; i <= 10; ++i) {
		EXPECT_EQ(sa.Locate(i), i);
	}
	EXPECT_EQ(sa.Locate(120), LOCATE_FAILED); 
}

TEST(NormalTest, SEQ_LIST_getData) {
	int test_case[] = { -1,2,44,23,-223,11,24,25,5,2,3,2311 };
	mylib::SeqList<int>sa{ -1,2,44,23,-223,11,24,25,5,2,3,2311 };
	int get;
	for (auto i = 0; i < sa.Length(); ++i)
	{
		EXPECT_TRUE(sa.getData(i+1, get));
		EXPECT_EQ(get, test_case[i]);
	}
}

TEST(NormalTest, SEQ_LIST_setData) {
	int test_case[] = { -1,2,44,23,-223,11,24,25,5,2,3,2311 };
	mylib::SeqList<int>sa;
	for (auto i = 0; i < sa.Length(); ++i)
	{
		sa.setData(i + 1, test_case[i]);
		int get;
		EXPECT_TRUE(sa.getData(i + 1, get));
		EXPECT_EQ(test_case[i], get);
	}
}

TEST(NormalTest, SEQ_LIST_insert) {
	int test_case[] = { -1,2,44,23,-223,11,24,25,5,2,3,2311 };
	mylib::SeqList<int>sa_1{ -1 };
	mylib::SeqList<int>sa_2{ -1, 2 };
	mylib::SeqList<int>sa_3{ -1, 2, 44 };
	mylib::SeqList<int>sa_4{ -1,2,44,23 };
	mylib::SeqList<int>sa_5{ -1, 2, 44, 23, -223 };
	mylib::SeqList<int>sa_6{ -1,2,44,23,-223,11 };
	mylib::SeqList<int>sa_7{ -1, 2, 44, 23, -223, 11, 24 };
	mylib::SeqList<int>sa_8{ -1,2,44,23,-223,11,24,25 };
	mylib::SeqList<int>sa_9{ -1, 2, 44, 23, -223, 11, 24, 25, 5 };
	mylib::SeqList<int>sa_10{ -1,2,44,23,-223,11,24,25,5,2 };
	mylib::SeqList<int>sa_11{ -1, 2, 44, 23, -223, 11, 24, 25, 5, 2, 3 };
	mylib::SeqList<int>sa_12{ -1,2,44,23,-223,11,24,25,5,2,3,2311 };
	std::vector<mylib::SeqList<int>>sa_s{ sa_1, sa_2,sa_3,sa_4,sa_5,sa_6,sa_7,sa_8,sa_9,sa_10,sa_11,sa_12};
	for (auto val = 0; val < 12; ++val) {

		for (auto i = 0; i < val; ++i) {
			EXPECT_TRUE(sa_s[val] .Insert(val, test_case[i]));
			//EXPECT_TRUE(sa_s[val].Length(), val + i+2);
			for (auto j = 0; j <= i; ++j)
			{
				int get;
				sa_s[val].getData(j + 1, get);
				EXPECT_EQ(test_case[j], get);
			}
		}
	}
}

TEST(NormalTest, SEQ_LIST_remove) {
	mylib::SeqList<int>sa{ -1,2,44,23,-223,11,24,25,5,2,3,2311 };
	std::vector<int>case_{ -1,2,44,23,-223,11,24,25,5,2,3,2311 };
	int get;
	int index = rand()%12+1;
	sa.Remove(index, get);
	case_.erase(case_.begin() + 2);
	for (auto i = 0; i < 11; ++i)
	{
		int g;
		sa.getData(i+1, g);
		EXPECT_EQ(g, case_[i]);
	}
	mylib::SeqList<int>sa_2{ -1,2,44,23,-223,11,24,25,5,2,3,2311 };
	std::vector<int>case_2{ -1,2,44,23,-223,11,24,25,5,2,3,2311 };
	for (auto i = 0; i < 12; ++i) {
		sa_2.Remove(1, get);
		case_2.erase(case_2.begin());
		EXPECT_EQ(sa_2.Length(), 11 - i);
		for (auto j = 0; j < 11-i; ++j)
		{
			int g;
			sa_2.getData(j + 1, g);
			EXPECT_EQ(g, case_2[j]);
		}
	}
	mylib::SeqList<int>sa_3{ -1,2,44,23,-223,11,24,25,5,2,3,2311 };
	std::vector<int>case_3{ -1,2,44,23,-223,11,24,25,5,2,3,2311 };
	for (auto i = 0; i < 12; ++i) {
		sa_3.Remove(12-i, get);
		case_3.erase(case_3.end()-1);
		EXPECT_EQ(sa_3.Length(), 11 - i);
		for (auto j = 0; j < 11 - i; ++j)
		{
			int g;
			sa_3.getData(j + 1, g);
			EXPECT_EQ(g, case_3[j]);
		}
	}
}

TEST(NormalTest, SEQ_LIST_isempty) {
	mylib::SeqList<int>sa_1;
	EXPECT_TRUE(sa_1.IsEmpty());
	mylib::SeqList<int>sa_2{ -1,2 };
	EXPECT_FALSE(sa_2.IsEmpty());
	int get;
	sa_2.Remove(1, get);
	sa_2.Remove(1, get);
	EXPECT_TRUE(sa_2.IsEmpty());
}

TEST(NormalTest, SEQ_LIST_isfull) {
	mylib::SeqList<int>sa_1{ {1,2},3 };
	EXPECT_FALSE(sa_1.IsFull());
	mylib::SeqList<int>sa_2{ {1,2},2 };
	EXPECT_TRUE(sa_2.IsFull());
}
/*
TEST(NormalTest, SEQ_LIST_sort) {
	mylib::SeqList<int>sa_1{ -10,-9,-20,1,44,2,3};
	std::vector<int>case_a{ -20,-10,-9,1,2,3,44 };
	std::vector<int>case_d{ 44,3,2,1,-9,-10,-20 };
	sa_1.Sort_A();
	for (auto i = 0; i < 7; ++i) {
		int get;
		sa_1.getData(i + 1, get);
		EXPECT_EQ(get, case_a[i]);
	}
	sa_1.Sort_D();
	for (auto i = 0; i < 7; ++i) {
		int get;
		sa_1.getData(i + 1, get);
		EXPECT_EQ(get, case_d[i]);
	}
}
*/

TEST(NormalTest, iterators) {
	mylib::SeqList<int>sa{ 1,2,3,4,5,6,7 };
	int i = 0;
	for(auto iter = sa.cbegin();)
}