#include "pch.h"
#include"List.h"
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
TEST_P(ArraySizeTest, SEQ_LIST_re_size) {
	int n = GetParam();
	mylib::SeqList<int>sa(n);
}
