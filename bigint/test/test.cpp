#include <gtest/gtest.h>
#include "bigint.h"

using namespace std;

TEST(Construct, bg) {
	BigInt bg{ "123456789" };
	EXPECT_EQ(string(bg), "123456789");
}

TEST(Construct, nbg) {
	BigInt bg{ "-1" };
	EXPECT_EQ(string(bg), "-1");
}

TEST(CopyConstr, bg) {
	BigInt bg{ "10" };
	BigInt bg1{ bg };
	EXPECT_EQ("10", string(bg1));
}

TEST(MoveConstr, bg) {
	BigInt bg{ "10" };
	BigInt bg1{ move(bg) };
	EXPECT_EQ("10", string(bg1));
}

TEST(Move, bg) {
	BigInt bg{ "10" };
	BigInt bg1{ "-999"};
	bg = move(bg1);
	EXPECT_EQ(string(bg), "-999");
	EXPECT_EQ(string(bg1), "10");
}

TEST(Copy, bg) {
	BigInt bg{ "10" };
	BigInt bg1{ "-999" };
	bg = bg1;
	EXPECT_EQ(string(bg), "-999");
	EXPECT_EQ(string(bg1), "-999");
}

TEST(Plus, bg) {
	BigInt bg{ "10" };
	BigInt bg1{ "-999" };
	EXPECT_ANY_THROW(bg + bg1);
}

TEST(Plus, bg1) {
	BigInt bg{ "10" };
	BigInt bg1{ "-9" };
	EXPECT_EQ(string(bg + bg1), "1");
}

TEST(Plus, bg2) {
	BigInt bg{ "10" };
	BigInt bg1{ "2" };
	EXPECT_EQ(string(bg + bg1), "12");
}

TEST(Minus, bg) {
	BigInt bg{ "100000000000" };
	BigInt bg1{ "222222" };
	EXPECT_EQ(string(bg - bg1), "99999777778");
}

TEST(Minus, bg1) {
	BigInt bg{ "1" };
	BigInt bg1{ "-22" };
	EXPECT_EQ(string(bg - bg1), "23");
}

TEST(Minus, bg2) {
	BigInt bg{ "-1" };
	BigInt bg1{ "-22" };
	EXPECT_EQ(string(bg - bg1), "21");
}

TEST(Mul, bg) {
	BigInt bg{ "-1" };
	BigInt bg1{ "-22" };
	EXPECT_EQ(string(bg * bg1), "22");
}

TEST(Mul, bg1) {
	BigInt bg{ "0" };
	BigInt bg1{ "-22" };
	EXPECT_EQ(string(bg * bg1), "0");
}

TEST(Mul, bg2) {
	BigInt bg{ "-12" };
	BigInt bg1{ "3" };
	EXPECT_EQ(string(bg * bg1), "-36");
}

TEST(Mul, bg3) {
	BigInt bg{ "545227779" };
	BigInt bg1{ "1234567890" };
	EXPECT_EQ(string(bg * bg1), "673120708689416310");
}

TEST(Cmp, bg) {
	BigInt bg{ "1" };
	BigInt bg1{ "2" };
	BigInt bg2{ "1" };
	EXPECT_TRUE(bg == bg2);
	EXPECT_FALSE(bg == bg1);
	EXPECT_TRUE(bg < bg1);
	EXPECT_TRUE(bg1 > bg);
}

TEST(PlusInt, bg) {
	BigInt bg{ "100" };
	EXPECT_EQ(string(bg + int32_t(12)), "112");
}

TEST(MinusInt, bg) {
	BigInt bg{ "100" };
	EXPECT_EQ(string(bg - int32_t(12)), "88");
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}