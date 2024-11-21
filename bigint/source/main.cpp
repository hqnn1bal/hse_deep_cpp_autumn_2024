#include "bigint.h"
#include <iostream>

int main(int argc, char* argv[]) {
	try {
		BigInt bg{ "-111" };
		BigInt bg1{ "10" };
		std::cout << bg * int32_t(-3);
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
}