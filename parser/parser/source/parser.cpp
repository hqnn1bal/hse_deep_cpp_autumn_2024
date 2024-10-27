#include "parser.h"
#include <sstream>

void Tokenparser::Parse(const std::string& str)
{
	if (this->startParseCallback) this->startParseCallback();

	std::stringstream ss;

	auto containsLetters = [](const std::string& str) {
		for (char symb : str) {
			if ((symb >= 'A' and symb <= 'Z') or (symb >= 'a' and symb <= 'z')) {
				return true;
			}
		}
		return false;
	};

	for (auto& symb : str) {
		if (symb == ' ' or symb == '\t' or symb == '\n') {
			if (ss.str().empty()) continue;
			if (containsLetters(ss.str())) {
				if (this->stringCallBack) this->stringCallBack(ss.str());
			}
			else {
				try {
					if (this->digitCallback) this->digitCallback(uint64_t(std::stoull(ss.str())));
				}
				catch (std::out_of_range& e) {
					if (this->stringCallBack) this->stringCallBack(ss.str());
				}
			}
			ss.str("");
			ss.clear();
			continue;
		}
		ss << symb;		
	}

	if (!ss.str().empty()) {
		if (containsLetters(ss.str())) {
			if (this->stringCallBack) this->stringCallBack(ss.str());
		}
		else {
			try {
				if (this->digitCallback) this->digitCallback(uint64_t(std::stoull(ss.str())));
			}
			catch (std::out_of_range& e) {
				if (this->stringCallBack) this->stringCallBack(ss.str());
			}
		}
	}

	if (this->endParseCallback) this->endParseCallback();
}