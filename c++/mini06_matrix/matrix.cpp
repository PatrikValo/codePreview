#include "matrix.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const matrix& mt) {
	for (size_t row = 0; row < mt.rows(); row++) {
		const char* sep = "";
		for (size_t col = 0; col < mt.cols(); col++) {
			out << sep << mt[{ row, col }];
			sep = ", ";
		}
		out << '\n';
	}
	return out;
}

/*********** TODO - Operators ************/
bool operator==(const matrix& a, const matrix& b) {
	if (a.rows() != b.rows())
		return false;
	if (a.cols() != b.cols())
		return false;
	for (size_t i = 0; i < a.matrix_.size(); ++i) {
		if (a.matrix_[i] != b.matrix_[i])
			return false;
	}
	return true;
}

bool operator!=(const matrix& a, const matrix& b) {
	return !(a == b);
}

matrix& matrix::operator+=(const matrix& b) {
	if (rows_ != b.rows() || cols_ != b.cols())
		throw std::invalid_argument("Problem");
	for (size_t i = 0; i < (rows_ * cols_); ++i) {
		matrix_[i] += b.matrix_[i];
	}
	return *this;
}

matrix operator+(matrix a, const matrix& b) {
	a += b;
	return a;
}

matrix& matrix::operator-=(const matrix& b) {
	if (rows_ != b.rows() || cols_ != b.cols())
		throw std::invalid_argument("Problem");
	for (size_t i = 0; i < (rows_ * cols_); ++i) {
		matrix_[i] -= b.matrix_[i];
	}
	return *this;
}

matrix operator-(matrix a, const matrix& b) {
	a -= b;
	return a;
}

matrix& matrix::operator*=(int scalar) {
	for (size_t i = 0; i < (rows_ * cols_); ++i) {
		matrix_[i] *= scalar;
	}
	return *this;
}
matrix operator*(matrix a, int scalar) {
	a *= scalar;
	return a;
}
matrix operator*(int scalar, matrix a) {
	a *= scalar;
	return a;
}
