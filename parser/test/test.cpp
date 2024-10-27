#include <gtest/gtest.h>
#include "parser.h"
#include <vector>
#include <string>

TEST(StandartTest, st) {
	Tokenparser tp{};
	std::vector<uint64_t> digits;
	std::vector<std::string> words;
	tp.SetDigitTokenCallback([&digits](uint64_t digit) -> void {
		digits.push_back(digit);
		});
	tp.SetStringTokenCallback([&words](const std::string& str) -> void {
		words.push_back(str);
		});
	std::string str = "		12	56\t uio		www ";
	tp.Parse(str);
	EXPECT_EQ(digits, std::vector<uint64_t>({12,56}));
	EXPECT_EQ(words, std::vector<std::string>({"uio", "www"}));
}

TEST(EmptyTest, empty) {
	Tokenparser tp{};
	std::vector<uint64_t> digits;
	std::vector<std::string> words;
	tp.SetDigitTokenCallback([&digits](uint64_t digit) -> void {
		digits.push_back(digit);
		});
	tp.SetStringTokenCallback([&words](const std::string& str) -> void {
		words.push_back(str);
		});
	std::string str = "";
	tp.Parse(str);
	EXPECT_EQ(0, digits.size());
	EXPECT_EQ(0, words.size());
}

TEST(OnlySep, sep) {
	Tokenparser tp{};
	std::vector<uint64_t> digits;
	std::vector<std::string> words;
	tp.SetDigitTokenCallback([&digits](uint64_t digit) -> void {
		digits.push_back(digit);
		});
	tp.SetStringTokenCallback([&words](const std::string& str) -> void {
		words.push_back(str);
		});
	std::string str = "				     \t\t\t\t		";
	tp.Parse(str);
	EXPECT_EQ(0, digits.size());
	EXPECT_EQ(0, words.size());
}
