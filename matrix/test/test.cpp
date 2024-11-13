#include<gtest/gtest.h>
#include "matrix.h"
#include <iostream>

TEST(InitTest, Matrix) {
	Matrix m(2,2);
	int num = 1;
	for (int i = 0; i < m.get_rows(); ++i) {
		for (int j = 0; j < m.get_columns(); ++j) {
			m[i][j] = num;
		}
	}
	EXPECT_EQ(m[0][0], 1);
	EXPECT_EQ(m[0][1], 1);
	EXPECT_EQ(m[1][0], 1);
	EXPECT_EQ(m[1][1], 1);
}

TEST(Gettest, Matrix) {
	Matrix m(1, 1);
	m[0][0] = 123;
	EXPECT_TRUE(m[0][0] == 123);
}

TEST(SumTest, Matrix) {
	Matrix m(2, 2);
	int num = 1;
	for (int i = 0; i < m.get_rows(); ++i) {
		for (int j = 0; j < m.get_columns(); ++j) {
			m[i][j] = num;
			num += 1;
		}
	}
	Matrix m1(2, 2);
	for (int i = 0; i < m1.get_rows(); ++i) {
		for (int j = 0; j < m1.get_columns(); ++j) {
			m1[i][j] = num;
			num += 1;
		}
	}
	Matrix m2 = m + m1;
	EXPECT_EQ(m2[0][0], 6);
	EXPECT_EQ(m2[0][1], 8);
	EXPECT_EQ(m2[1][0], 10);
	EXPECT_EQ(m2[1][1], 12);
}

TEST(MulTest, Matrix) {
	Matrix m(2, 2);
	int num = 1;
	for (int i = 0; i < m.get_rows(); ++i) {
		for (int j = 0; j < m.get_columns(); ++j) {
			m[i][j] = num;
			num += 1;
		}
	}
	m *= 2;
	EXPECT_EQ(m[0][0], 2);
	EXPECT_EQ(m[0][1], 4);
	EXPECT_EQ(m[1][0], 6);
	EXPECT_EQ(m[1][1], 8);
}

TEST(EqTest, Matrix) {
	Matrix m(2, 2);
	int num = 1;
	for (int i = 0; i < m.get_rows(); ++i) {
		for (int j = 0; j < m.get_columns(); ++j) {
			m[i][j] = num;
			num += 1;
		}
	}
	Matrix m1(2, 2);
	int num1 = 1;
	for (int i = 0; i < m1.get_rows(); ++i) {
		for (int j = 0; j < m1.get_columns(); ++j) {
			m1[i][j] = num1;
			num1 += 1;
		}
	}
	EXPECT_TRUE(m == m1);
	m1[0][0] = 0;
	EXPECT_TRUE(m != m1);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
