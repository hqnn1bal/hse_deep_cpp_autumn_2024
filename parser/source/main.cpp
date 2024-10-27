#include "parser.h"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
	Tokenparser tp{};
	std::vector<uint64_t> v;
	tp.SetStartCallback([]() -> void {
		std::cout << "Start parsing:" << std::endl;
		});
	tp.SetDigitTokenCallback([&v](uint64_t digit) -> void {
		std::cout << "Digit token: " << digit << std::endl;
		v.push_back(digit);
		});
	tp.SetStringTokenCallback([](const std::string& str) -> void {
		std::cout << "String token: " << str << std::endl;
	});
	tp.SetEndCallback([&v]() -> void {
		std::cout << "End parsing)" << std::endl;
		std::cout << "Digit token count:" << v.size() << std::endl;
		for (auto val : v) {
			std::cout << val << " ";
		}
		std::cout << std::endl;
		});
	std::string str = "tyr24\n			 122  9090 pl 3 hgfhgh567	yutyu iyooyo	666 uiui l 89898";
	tp.Parse(str);
}