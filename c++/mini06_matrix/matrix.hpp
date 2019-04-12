#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <utility>
#include <vector>

class matrix {
public:
	using value_type = int;

private:
	std::vector<value_type> matrix_;
	std::size_t rows_; // number of rows
	std::size_t cols_; // number of columns

public:
	matrix(std::size_t rows, std::size_t cols)
	    : matrix_(rows * cols)
	    , rows_(rows)
	    , cols_(cols) {}

	matrix(const std::vector<value_type>& data, std::size_t rows)
	    : matrix_(data.size() % rows == 0
	              ? data
	              : throw std::invalid_argument("Input data has incompatible size"))
	    , rows_(rows)
	    , cols_(data.size() / rows) {}

	// Returns number of rows, number of columns
	std::pair<std::size_t, std::size_t> size() const {
		return { rows_, cols_ };
	}

	// Returns number of rows
	std::size_t rows() const { return rows_; }

	// Returns number of columns
	std::size_t cols() const { return cols_; }

	/******* TODO - Operators *******/
	// operator[] takes a pair { row index, column index } where
	// - row index is in range [0, rows)
	// - column index is in range [0, cols)

	friend bool operator==(const matrix& a, const matrix& b);
	matrix& operator+=(const matrix& b);
	matrix& operator-=(const matrix& b);
	matrix& operator*=(int scalar);

	value_type& operator[](std::pair<std::size_t, std::size_t> size) {
		if (size.first > rows_ - 1 || size.second > cols_ - 1)
			throw std::out_of_range("Problem");
		return matrix_[(cols_ * size.first) + size.second];
	}
	value_type operator[](std::pair<std::size_t, std::size_t> size) const {
		if (size.first > rows_ - 1 || size.second > cols_ - 1)
			throw std::out_of_range("Problem");
		return matrix_[(cols_ * size.first) + size.second];
	}
};

std::ostream& operator<<(std::ostream&, const matrix&);

/****** TODO - Operators *******/
//bool operator==(const matrix& a, const matrix& b);
bool operator!=(const matrix& a, const matrix& b);
matrix operator+(matrix a, const matrix& b);
matrix operator-(matrix a, const matrix& b);
matrix operator*(matrix a, int scalar);
matrix operator*(int scalar, matrix a);
#endif
