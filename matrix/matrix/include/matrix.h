#pragma once
#include <cstdint>
#include <stdexcept>

class Matrix {
private:
    int32_t* data_;
    size_t rows_;
    size_t columns_;
public:
    Matrix(size_t n, size_t m);
    Matrix() : Matrix(0, 0) {};
    Matrix(const Matrix& mtrx);
    ~Matrix() { delete[] data_; }

    inline int32_t get_rows() const noexcept { return rows_; }
    inline int32_t get_columns() const noexcept { return columns_; }

    class Row {
    private:
        int32_t* ptr_;
        size_t size_;
    public:
        Row(int32_t* ptr, size_t size) : ptr_(ptr), size_(size) {}
        int32_t& operator[](size_t index) { 
            if (index >= size_) throw std::out_of_range("");
            return ptr_[index]; 
        }
        const int32_t& operator[](size_t index) const { 
            if (index >= size_) throw std::out_of_range("");
            return ptr_[index]; 
        }
    };

    Row operator[](size_t index) { 
        if (index >= rows_) throw std::out_of_range("");
        return Row(data_ + index * columns_, columns_); 
    }
    const Row operator[](size_t index) const { 
        if (index >= rows_) throw std::out_of_range("");
        return Row(data_ + index * columns_, columns_); 
    }  
    Matrix& operator*=(double l) noexcept;
    Matrix operator+(const Matrix& m);
    bool operator==(const Matrix& mtrx) noexcept;
    bool operator!=(const Matrix& mtrx) noexcept;
};

std::ostream& operator<<(std::ostream& os, const Matrix& mtrx) noexcept;