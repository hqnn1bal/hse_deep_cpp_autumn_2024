#include "bigint.h"
#include <iomanip>

BigInt::operator int32_t() const {
	if ((*this).size_ > 10) throw std::runtime_error("To big to cast to int32_t");

	std::string nums = std::string(const_cast<BigInt&>(*this));
	
	if ((*this).isNegative_) {
		return -1 * static_cast<int32_t>(std::stoi([](std::string s) -> std::string {
			std::string s1;
			for (int i = 1; i < s.size(); ++i) {
				s1.push_back(s[i]);
			}

			return s1;
			}(nums)));
	}
	else {
		return static_cast<int32_t>(std::stoi(nums));
	}
}

BigInt::operator std::string() const noexcept {
	std::string s = "";

	if (this->isNegative_) s.push_back('-');

	for (size_t i = 0; i < (*this).size_; ++i) {
		s.push_back((*this).data_[i]);
	}

	return s;
}

BigInt::BigInt(size_t n) {
	if (n == 0) return;
	
	(*this).data_ = new char[n + 1]{};
	data_[n] = '\0';
	(*this).size_ = n;
	return;
}

BigInt::BigInt(BigInt&& bg) noexcept {
	std::swap((*this).data_, bg.data_);
	std::swap((*this).size_, bg.size_);
	std::swap((*this).isNegative_, bg.isNegative_);
}

BigInt::BigInt(const BigInt& bg) noexcept {
	(*this).data_ = new char[bg.size_ + 1] {};
	(*this).data_[bg.size_] = '\0';
	(*this).size_ = bg.size_;

	for (size_t i = 0; i < (*this).size_; ++i) {
		(*this).data_[i] = bg.data_[i];
	}
}

BigInt& BigInt::operator=(const BigInt& bg) noexcept {
	if (&bg == this) return *this;
	delete[] (*this).data_;
	(*this).size_ = bg.size_;

	(*this).data_ = new char[(*this).size_] {};

	for (size_t i = 0; i < (*this).size_; ++i) {
		(*this).data_[i] = bg.data_[i];
	}

	(*this).isNegative_ = bg.isNegative_;

	return *this;
}

BigInt& BigInt::operator=(BigInt&& bg) noexcept {
	if (&bg == this) return *this;
	std::swap((*this).data_, bg.data_);
	std::swap((*this).size_, bg.size_);
	std::swap((*this).isNegative_, bg.isNegative_);
}

BigInt::BigInt(const std::string& num) {
	if (num.size() == 0) return;

	std::string num1 = const_cast<std::string&>(num);

	if (num1[0] == '-') {
		isNegative_ = true;
		num1 = [](std::string s) -> std::string {
			std::string s1;
			for (int i = 1; i < s.size(); ++i) {
				s1.push_back(s[i]);
			}

			return s1;
			}(num1);
	}

	(*this).data_ = new char[num1.size() + 1]{};
	(*this).size_ = num1.size();

	for (size_t i = 0; i < (*this).size_; ++i) {
		(*this).data_[i] = num1[i];
	}
	
	(*this).data_[num1.size()] = '\0';

	return;
}

std::ostream& operator<<(std::ostream& os, const BigInt& bg) noexcept {
	if (bg.isNegative_) os << "-";
	for (size_t i = 0; bg.data_[i] != '\0'; ++i) {
		os << bg.data_[i];
	}
	os << std::endl;

	return os;
}

BigInt BigInt::operator+(const BigInt& bg) {
	if ((*this).isNegative_ && bg.isNegative_) {
		(*this).isNegative_ = false;
		BigInt& bg1 = const_cast<BigInt&>(bg);
		bg1.isNegative_ = false;

		BigInt res = std::move(bg1 + (*this));
		-res;
		return (res);
	}

	if (!(*this).isNegative_ && bg.isNegative_) {
		(*this).isNegative_ = false;
		BigInt& bg1 = const_cast<BigInt&>(bg);
		bg1.isNegative_ = false;
		return (*this) - bg1;
	}

	if ((*this).isNegative_ && !bg.isNegative_) {
		(*this).isNegative_ = false;
		BigInt& bg1 = const_cast<BigInt&>(bg);
		bg1.isNegative_ = false;
		return bg1 - (*this);
	}

	size_t len1 = (*this).size_;
	size_t len2 = bg.size_;

	int i = static_cast<int>(len1) - 1;
	int j = static_cast<int>(len2) - 1;
	size_t maxl = std::max(len1, len2);
	size_t pos = maxl - 1;

	BigInt res(maxl);

	int carry = 0;

	while (i >= 0 || j >= 0 || carry > 0) {
		int digit1 = (i >= 0) ? (*this).data_[i] - '0' : 0;
		int digit2 = (j >= 0) ? bg.data_[j] - '0' : 0;

		int sum = digit1 + digit2 + carry;
		res.data_[pos--] = (sum % 10) + '0';
		carry = sum / 10;

		--i;
		--j;
	}
	
	if (pos == 0 && res.data_[0] == '0') {
		char* trim = new char[maxl];
		std::strcpy(trim, res.data_ + 1);
		delete[] res.data_;
		res.size_ = maxl;
		res.data_ = trim;
	}
	
	return res;
}

BigInt BigInt::operator-(const BigInt& bg) {
	if (((*this).isNegative_ && bg.isNegative_)) {
		(*this).isNegative_ = false;
		BigInt& bg1 = const_cast<BigInt&>(bg);
		bg1.isNegative_ = false;
		return (bg1 - (*this));
	}

	if (!(*this).isNegative_ && bg.isNegative_) {
		(*this).isNegative_ = false;
		BigInt& bg1 = const_cast<BigInt&>(bg);
		bg1.isNegative_ = false;
		return ((*this) + bg1);
	}

	if ((*this).isNegative_ && !bg.isNegative_) {
		(*this).isNegative_ = false;
		BigInt& bg1 = const_cast<BigInt&>(bg);
		bg1.isNegative_ = false;

		BigInt res = std::move(bg1 + (*this));
		-res;
		return (res);
	}

    size_t len1 = this->size_;
    size_t len2 = bg.size_;

	if (len1 < len2) throw std::runtime_error("Cant op- < 0");

    int i = static_cast<int>(len1) - 1; 
    int j = static_cast<int>(len2) - 1; 
    size_t maxl = std::max(len1, len2);

    BigInt res(maxl); 

    res.data_[maxl] = '\0'; 

    int borrow = 0; 

    while (i >= 0 || j >= 0) {
        int digit1 = (i >= 0) ? this->data_[i] - '0' : 0;
        int digit2 = (j >= 0) ? bg.data_[j] - '0' : 0;

        int diff = digit1 - digit2 - borrow;

        if (diff < 0) {
            diff += 10; 
            borrow = 1;
        }
        else {
            borrow = 0;
        }

        res.data_[i] = diff + '0'; 
        --i;
        --j;
    }

    size_t start = 0;
    while (start < maxl - 1 && res.data_[start] == '0') {
        ++start;
    }

    if (start > 0) {
        size_t newSize = maxl - start;
        char* trim = new char[newSize + 1];
        std::strncpy(trim, res.data_ + start, newSize);
        trim[newSize] = '\0';
        delete[] res.data_;
        res.data_ = trim;
        res.size_ = newSize;
    }

    return res;
}

void BigInt::operator-() noexcept {
	isNegative_ = true;
}

BigInt BigInt::operator*(const BigInt& bg) noexcept {

	if (std::strcmp(std::string(*this).c_str(), "0") == 0 || std::strcmp(std::string(bg).c_str(),"0") == 0) {
		return BigInt("0");
	}

	if ((*this).size_ <= 8 && bg.size_ <= 8) {
		int32_t res = (int32_t(*this)) * int32_t(const_cast<BigInt&>(bg));
		if (isNegative_ && bg.isNegative_) return BigInt(std::to_string(res));
		if ((!isNegative_ && bg.isNegative_) || (isNegative_ && !bg.isNegative_)) return BigInt(std::to_string(res));
		return BigInt(std::to_string(res));
	}
	
	size_t result_size = size_ + bg.size_;
	char* result = new char[result_size];
	std::fill(result, result + result_size, 0);

	for (size_t i = 0; i < size_; ++i) {
		int digit1 = data_[size_ - 1 - i] - '0';
		int carry = 0;
		for (size_t j = 0; j < bg.size_; ++j) {
			int digit2 = bg.data_[bg.size_ - 1 - j] - '0';
			int temp = result[i + j] + digit1 * digit2 + carry;
			result[i + j] = temp % 10;
			carry = temp / 10;
		}
		if (carry > 0) {
			result[i + bg.size_] += carry;
		}
	}

	size_t actual_size = result_size;
	while (actual_size > 1 && result[actual_size - 1] == 0) {
		--actual_size;
	}

	char* result_data = new char[actual_size + 1];
	for (size_t i = 0; i < actual_size; ++i) {
		result_data[i] = result[actual_size - 1 - i] + '0';
	}
	result_data[actual_size] = '\0';
	delete[] result;

	bool result_negative = isNegative_ != bg.isNegative_;
	return BigInt(result_data, actual_size, result_negative);
}

bool BigInt::operator==(const BigInt& bg) const noexcept {
	return (std::string(*this) == std::string(bg));
}

bool BigInt::operator!=(const BigInt& bg) const noexcept {
	return !(*this == bg);
}

bool BigInt::operator<(const BigInt& bg) const noexcept {
	return (std::string(*this) < std::string(bg));
}

bool BigInt::operator>(const BigInt& bg) const noexcept {
	return (std::string(*this) > std::string(bg));
}

bool BigInt::operator<=(const BigInt& bg) const noexcept {
	return !(*this > bg);
}
 
bool BigInt::operator>=(const BigInt& bg) const noexcept {
	return !(*this < bg);
}