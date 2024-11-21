#pragma once
#include <string>
#include <iostream>

class BigInt {
private:
	char* data_ = nullptr;
	size_t size_ = 0;
	bool isNegative_ = false;
public:
	explicit operator int32_t () const;
	explicit operator std::string() const noexcept;
	explicit BigInt(size_t n);
	BigInt(char* arr, size_t size, bool neg) : data_(arr), size_(size), isNegative_(neg) {};
	BigInt() : BigInt("") {};
	BigInt(const std::string& num);
	BigInt(BigInt&& bg) noexcept;
	BigInt(const BigInt& bg) noexcept;
	BigInt& operator=(BigInt&& bg) noexcept;
	BigInt& operator=(const BigInt& bg) noexcept;
	friend std::ostream& operator<<(std::ostream& os, const BigInt& bg) noexcept;
	BigInt operator+(const BigInt& bg);
	void operator-() noexcept;
	BigInt operator-(const BigInt& bg);
	BigInt operator*(const BigInt& bg) noexcept;
	bool operator==(const BigInt& bg) const noexcept;
	bool operator!=(const BigInt& bg) const noexcept;
	bool operator<(const BigInt& bg) const noexcept;
	bool operator>(const BigInt& bg) const noexcept;
	bool operator<=(const BigInt& bg) const noexcept;
	bool operator>=(const BigInt& bg) const noexcept;
	__forceinline BigInt operator+(int32_t num) const {
		return const_cast<BigInt&>(*this) + BigInt(std::to_string(num));
	}
	__forceinline BigInt operator-(int32_t num) const {
		return const_cast<BigInt&>(*this) - BigInt(std::to_string(num));
	}
	__forceinline BigInt operator*(int32_t num) const {
		return const_cast<BigInt&>(*this) * BigInt(std::to_string(num));
	}
	~BigInt() { delete[] data_; }
};

__forceinline BigInt operator-(const std::string& s, const BigInt& bg) { return BigInt(s) - bg; }
__forceinline BigInt operator+(const std::string & s, const BigInt & bg) { return BigInt(s) + bg; }