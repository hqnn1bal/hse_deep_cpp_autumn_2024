#include <functional>
#include <any>

class Tokenparser {
private:
	std::function<void()> startParseCallback;
	std::function<void()> endParseCallback;
	std::function<std::any(std::uint64_t)> digitCallback;
	std::function<std::any(const std::string&)> stringCallBack;
public:
	Tokenparser() {};

	inline void SetStartCallback(std::function<void()> func) { this->startParseCallback = func; };
	inline void SetEndCallback(std::function<void()> func) { this->endParseCallback = func; }
	inline void SetDigitTokenCallback(std::function<std::any(std::uint64_t digit)> func) { this->digitCallback = func; }
	inline void SetStringTokenCallback(std::function<std::any(const std::string& str)> func) { this->stringCallBack = func; }
	void Parse(const std::string&);
}; 