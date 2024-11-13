#include "matrix.h"
#include "matrix.h"
#include "matrix.h"
#include "matrix.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

Matrix::Matrix(size_t n, size_t m) {
	if (n < 0 || m < 0) throw std::invalid_argument("");
	if (n * m == 0 && (n != 0 || m != 0)) throw std::invalid_argument("");
	rows_ = n;
	columns_ = m;
	data_ = new int32_t[rows_ * columns_]{};
}

Matrix::Matrix(const Matrix& mtrx) : rows_(mtrx.rows_), columns_(mtrx.columns_)
{
	data_ = new int32_t[rows_ * columns_]{};

	for (size_t i = 0; i < rows_; ++i) {
		for (size_t j = 0; j < columns_; ++j) {
			(*this)[i][j] = mtrx[i][j];
		}
	}
}

Matrix& Matrix::operator*=(double l) noexcept {
	for (size_t i = 0; i < rows_; ++i) {
		for (size_t j = 0; j < columns_; ++j) {
			(*this)[i][j] *= l;
		}
	}
	return (*this);
}

Matrix Matrix::operator+(const Matrix& mtrx) {
	if (columns_ != mtrx.columns_ || rows_ != mtrx.rows_) throw std::invalid_argument("Matrices must be one sized");

	Matrix res(rows_, columns_);

	for (size_t i = 0; i < rows_; ++i) {
		for (size_t j = 0; j < columns_; ++j) {
			res.data_[i * res.columns_ + j] = data_[i * res.columns_ + j] + mtrx.data_[i * res.columns_ + j];
		}
	}

	return res;
}

bool Matrix::operator==(const Matrix& mtrx) noexcept
{
	for (size_t i = 0; i < rows_; ++i) {
		for (size_t j = 0; j < columns_; ++j) {
			if ((*this)[i][j] != mtrx[i][j]) return false;
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix& mtrx) noexcept
{
	return !((*this) == mtrx);
}

std::ostream& operator<<(std::ostream& os, const Matrix& mtrx) noexcept {
	size_t max_length1 = 0;
	size_t max_length = 0;

	std::stringstream ss1;

	for (int i = 0; i < mtrx.get_rows(); ++i) {
		ss1 << mtrx[i][0];
		max_length1 = std::max(ss1.str().size(), max_length1);
		ss1.str("");
	}

	std::stringstream ss;

	for (int i = 0; i < mtrx.get_rows(); ++i) {
		for (int j = 1; j < mtrx.get_columns(); ++j) {
			ss << mtrx[i][j];
			max_length = std::max(ss.str().size(), max_length);
			ss.str("");
		}
	}


	for (size_t i = 0; i < mtrx.get_rows(); ++i) {
		os << "|";
		for (size_t j = 0; j < mtrx.get_columns(); ++j) {
			if (j == 0) {
				os << std::setw(max_length1) << mtrx[i][j];
			}
			else {
				os << std::setw(max_length + 1) << mtrx[i][j];
			}
		}
		os << "|" << std::endl;
	}

	return os;
}
