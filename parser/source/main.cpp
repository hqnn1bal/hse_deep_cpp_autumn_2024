#include "parser.h"
#include <iostream>

int main(int argc, char* argv[]) {
	Tokenparser tp{};
	tp.SetStartCallback([]() -> void {
		std::cout << "Start parsing:" << std::endl;
		});
	tp.SetDigitTokenCallback([](uint64_t digit) -> std::any {
		std::cout << "Digit token: " << digit << std::endl;
		return std::any();
		});
	tp.SetStringTokenCallback([](const std::string& str) -> std::any {
		std::cout << "String token: " << str << std::endl;
		return std::any();
	});
	tp.SetEndCallback([]() -> void {
		std::cout << "End parsing)" << std::endl;
		});
	std::string str = "tyr24 hgfhgh567	yutyu iyooyo	l";
	tp.Parse(str);
}