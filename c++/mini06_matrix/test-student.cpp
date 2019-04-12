#include "catch.hpp"
#include "matrix.hpp"

using namespace std;

void fillMatrices(matrix &a, matrix &b) {
	if (a.size() != b.size())
		return;
	for (size_t i = 0; i < a.rows(); ++i) {
		for (size_t j = 0; j < a.cols(); ++j) {
			a[{ j, i }] = i * j;
			b[{ j, i }] = i + j;
		}
	}
}

TEST_CASE("Matrix equality operators ==/!=") {
	matrix a1{ 5, 5 }, b1{ 5, 5 };
	matrix a2{ 4, 5 }, b2{ 2, 10 };

	SECTION("operator==") {
		REQUIRE(a1 == b1);
		REQUIRE_FALSE(a2 == b2);
	}

	SECTION("operator!=") {
		REQUIRE(a2 != b2);
		REQUIRE_FALSE(a1 != b1);
	}
}

TEST_CASE("Matrix addition operators +/+=") {
	matrix a{ 5, 5 }, b{ 5, 5 };
	matrix res{ { 0, 1, 2, 3, 4,
		            1, 3, 5, 7, 9,
		            2, 5, 8, 11, 14,
		            3, 7, 11, 15, 19,
		            4, 9, 14, 19, 24 },
		5 };

	SECTION("all zeroes") {
		a = a + b;
		for (size_t i = 0; i < 5; ++i) {
			for (size_t j = 0; j < 5; ++j) {
				CHECK(a[{ j, i }] == 0);
			}
		}
	}

	fillMatrices(a, b);

	SECTION("operator+") {
		CHECK(a + b == res);
	}

	SECTION("operator+=") {
		a += b;
		CHECK(a == res);
	}

	SECTION("operator+= reversed") {
		b += a;
		CHECK(b == res);
	}
}

TEST_CASE("Multiplication by a scalar: operators */*=") {
	matrix::value_type scalar = 2;
	matrix m1({ 1, 0, 2,
	              -1, 3, 1 },
	    2);
	matrix res({ 2, 0, 4,
	               -2, 6, 2 },
	    2);
	SECTION("Scalar on the right") {
		auto aux_m = m1 * scalar;
		CHECK(aux_m == res);
	}

	SECTION("Scalar on the left") {
		auto aux_m = scalar * m1;
		CHECK(aux_m == res);
	}

	SECTION("Multiplication using *=") {
		m1 *= scalar;
		CHECK(m1 == res);
	}
}

TEST_CASE("Checking no_corr_result()", "no_corr_result") {
	matrix a{ 2, 3 }, b{ 2, 3 }, c{ 2, 4 };

	SECTION("operator+ with incompatible sizes") {
		CHECK_THROWS_AS(a + c, std::invalid_argument);
	}

	SECTION("operator+= with incompatible sizes") {
		CHECK_THROWS_AS(a += c, std::invalid_argument);
	}

	SECTION("operator- with incompatible sizes") {
		CHECK_THROWS_AS(a - c, std::invalid_argument);
	}

	SECTION("operator-= with incompatible sizes") {
		CHECK_THROWS_AS(a -= c, std::invalid_argument);
	}
}

// silence warnings; in C++17 it is better to use [[maybe_unused]]
#define UNUSED(var) (void)(var)

TEST_CASE("Const correctness of operators (compile-only)") {
	// This is a compile-only test.
	const matrix a{ 2, 3 }, b{ 2, 3 };
	matrix c = a + b;
	c += a;
	c = a - b;
	c -= a;
	c = 3 * a;
	c = a * 5;
	bool result = a == b;
	result = a != b;

	// correct return values
	matrix &ref1 = (c += a);
	matrix &ref2 = (c -= a);
	matrix &ref3 = (c *= 2);

	UNUSED(ref1);
	UNUSED(ref2);
	UNUSED(ref3);
}
TEST_CASE("TRY") {
	matrix a{ { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 }, 4 };
	CHECK(a[{ 0, 2 }] == 3);
	CHECK(a[{ 1, 1 }] == 5);
	CHECK(a[{ 2, 0 }] == 7);
	CHECK(a[{ 3, 2 }] == 12);
	CHECK(a[{ 0, 0 }] == 1);
}
TEST_CASE("TRY2") {
	matrix a{ { 1, 2, 3, 1, 4, 5, 6, 2, 7, 8, 9, 3, 10, 11, 12, 4, 5, 6, 7, 8 }, 5 };
	CHECK(a[{ 0, 3 }] == 1);
	CHECK(a[{ 1, 1 }] == 5);
	CHECK(a[{ 2, 0 }] == 7);
	CHECK(a[{ 3, 3 }] == 4);
	CHECK(a[{ 0, 0 }] == 1);
	CHECK(a[{ 4, 3 }] == 8);
	CHECK(a[{ 4, 0 }] == 5);
}
