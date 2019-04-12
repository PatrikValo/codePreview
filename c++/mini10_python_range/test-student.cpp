#include "range.hpp"
#include <iostream>
#include <vector>

#include "catch.hpp"

#include <stdexcept>

TEST_CASE("range basic") {
	SECTION("one argument") {
		int i = 0;
		for (int x : range(5)) {
			REQUIRE(i < 5);
			REQUIRE(x == i++);
		}

		auto r = range(5);
		REQUIRE(*std::next(r.begin(), 4) == 4);
		REQUIRE(std::next(r.begin(), 5) == r.end());
		REQUIRE(*r.begin() == 0);
		REQUIRE(*r.end() == 5);
		REQUIRE(*r.begin()++ == 0);
		REQUIRE(*++r.begin() == 1);
		REQUIRE(*r.end()-- == 5);
		REQUIRE(*--r.end() == 4);
	}

	SECTION("two arguments") {
		int i = 5;
		for (int x : range(5, 10)) {
			REQUIRE(i < 10);
			REQUIRE(x == i++);
		}
		auto r = range(5, 10);
		REQUIRE(*std::next(r.begin(), 4) == 9);
		REQUIRE(std::next(r.begin(), 5) == r.end());
	}

	SECTION("three arguments") {
		int i = 5;
		auto r = range(5, 100, 5);
		for (int x : r) {
			REQUIRE(i < 100);
			REQUIRE(x == i);
			i += 5;
		}
		REQUIRE(*std::next(r.begin(), 18) == 95);
		REQUIRE(std::next(r.begin(), 19) == r.end());
	}

	SECTION("with zero step") {
		REQUIRE_THROWS_AS(range(1, 2, 0), std::invalid_argument);
	}

	SECTION("with negative step") {
		int i = 10;
		auto r = range(10, 0, -1);
		for (int x : r) {
			REQUIRE(x == i);
			--i;
			REQUIRE(i >= 0);
		}
		REQUIRE(i == 0);
		REQUIRE(*std::next(r.begin(), 5) == 5);
		REQUIRE(*std::next(r.begin(), 9) == 1);
		REQUIRE(std::next(r.begin(), 10) == r.end());
	}
}

struct Integer {
	int integer;
	Integer(int i)
			:integer(i){}
	Integer& operator+=(const Integer& b) {
		integer += b.integer;
		return *this;
	}
	Integer operator++(int) {
		Integer newI(*this);
		integer++;
		return newI;
	}
	Integer operator++() {
		integer++;
		return *this;
	}
	Integer& operator-=(const Integer& b) {
		integer -= b.integer;
		return *this;
	}
	bool operator==(const Integer& a) const {
		return integer == a.integer;
	}

	bool operator!=(const Integer& a) const {
		return integer != a.integer;
	}
};
std::ostream &operator<<(std::ostream &out, const Integer &i) {
	out << "Integer{ " << i.integer << " }";
	return out;
}
bool operator<(const Integer& l, const Integer& r) {
	return l.integer < r.integer;
}
bool operator<=(const Integer& l, const Integer& r) {
	return l.integer <= r.integer;
}
bool operator>(const Integer& l, const Integer& r) {
	return l.integer > r.integer;
}

TEST_CASE("PRIMITIVE WITH STRUCT") {
	Integer a {0};
	Integer b {1};
	Integer c {10};
	auto r = range(a, c, b);
	auto it = r.begin();
	auto it2 = r.begin();
	REQUIRE(*it++ == a);
	REQUIRE(*it == b);
	REQUIRE(*++it2 == b);
	Integer i = Integer(0);
	for (Integer x : range(Integer(5))) {
		REQUIRE(x == i++);
	}
}

TEST_CASE("EXTENDED") {
	SECTION("INT") {
		int i = -5;
		for (int x : range(0, 13, 5)) {
			REQUIRE(x < 13);
			i += 5;
			REQUIRE(x == i);
		}
		REQUIRE(i == 10);
	}
	SECTION("INT2") {
		int i = -3;
		for (int x : range(0, 31, 3)) {
			REQUIRE(x < 31);
			i += 3;
			REQUIRE(x == i);
		}
		REQUIRE(i == 30);
	}
	SECTION("INT3") {
		int i = 13;
		for (int x : range(10, 0, -3)) {
			REQUIRE(x <= 10);
			REQUIRE(x > 0);
			i -= 3;
			REQUIRE(x == i);
		}
		REQUIRE(i == 1);
	}
	SECTION("UNSIGNED") {
		unsigned i = -5;
		for (unsigned x : range(0, 13, 5)) {
			REQUIRE(x < 13);
			i += 5;
			REQUIRE(x == i);
		}
		REQUIRE(i == 10);
	}
	SECTION("UNSIGNED2") {
		unsigned i = -3;
		for (unsigned x : range(0, 31, 3)) {
			REQUIRE(x < 31);
			i += 3;
			REQUIRE(x == i);
		}
		REQUIRE(i == 30);
	}
	SECTION("UNSIGNED3") {
		unsigned i = 13;
		for (unsigned x : range(10, 0, -3)) {
			REQUIRE(x <= 10);
			REQUIRE(x > 0);
			i -= 3;
			REQUIRE(x == i);
		}
		REQUIRE(i == 1);
	}
	SECTION("LONG") {
		long i = -5;
		for (long x : range(0, 13, 5)) {
			REQUIRE(x < 13);
			i += 5;
			REQUIRE(x == i);
		}
		REQUIRE(i == 10);
	}
	SECTION("LONG2") {
		long i = -3;
		for (long x : range(0, 31, 3)) {
			REQUIRE(x < 31);
			i += 3;
			REQUIRE(x == i);
		}
		REQUIRE(i == 30);
	}
	SECTION("LONG3") {
		long i = 13;
		for (long x : range(10, 0, -3)) {
			REQUIRE(x <= 10);
			REQUIRE(x > 0);
			i -= 3;
			REQUIRE(x == i);
		}
		REQUIRE(i == 1);
	}
	SECTION("STRUCT INTEGER") {
		Integer i = Integer(-5);
		for (Integer x : range(0, 13, 5)) {
			REQUIRE(x < Integer(13));
			i += 5;
			REQUIRE(x == i);
		}
		REQUIRE(i == Integer(10));
	}
	SECTION("STRUCT INTEGER2") {
		Integer i = Integer(-3);
		for (Integer x : range(0, 31, 3)) {
			REQUIRE(x < Integer(31));
			i += 3;
			REQUIRE(x == i);
		}
		REQUIRE(i == Integer(30));
	}
	SECTION("STRUCT INTEGER3") {
		Integer i = Integer(13);
		for (Integer x : range(10, 0, -3)) {
			REQUIRE(x <= Integer(10));
			REQUIRE(x > Integer(0));
			i -= 3;
			REQUIRE(x == i);
		}
		REQUIRE(i == Integer(1));
	}
}
TEST_CASE("NO ITERATIONS") {
    SECTION("INT") {
        for (int x : range(10, 5, 1)) {
            REQUIRE_FALSE("Pozor pretiekol for cyklus" != "Spravne riesenie");
            std::cout << x;
        }
        REQUIRE("Spravne riesenie" == "Spravne riesenie");
    }
	SECTION("INT2") {
		for (int x : range(0, 10, -1)) {
			REQUIRE_FALSE("Pozor pretiekol for cyklus" != "Spravne riesenie");
			std::cout << x;
		}
		REQUIRE("Spravne riesenie" == "Spravne riesenie");
	}
	SECTION("INT3") {
		for (int x : range(10, 0)) {
			REQUIRE_FALSE("Pozor pretiekol for cyklus" != "Spravne riesenie");
			std::cout << x;
		}
		REQUIRE("Spravne riesenie" == "Spravne riesenie");
	}
	SECTION("UNSIGNED") {
		for (unsigned x : range(10, 5, 1)) {
			REQUIRE_FALSE("Pozor pretiekol for cyklus" != "Spravne riesenie");
			std::cout << x;
		}
		REQUIRE("Spravne riesenie" == "Spravne riesenie");
	}
	SECTION("UNSIGNED2") {
		for (unsigned x : range(0, 10, -1)) {
			REQUIRE_FALSE("Pozor pretiekol for cyklus" != "Spravne riesenie");
			std::cout << x;
		}
		REQUIRE("Spravne riesenie" == "Spravne riesenie");
	}
	SECTION("UNSIGNED3") {
		for (unsigned x : range(1, 0)) {
			REQUIRE_FALSE("Pozor pretiekol for cyklus" != "Spravne riesenie");
			std::cout << x;
		}
		REQUIRE("Spravne riesenie" == "Spravne riesenie");
	}
	SECTION("LONG") {
		for (long x : range(10, 5, 1)) {
			REQUIRE_FALSE("Pozor pretiekol for cyklus" != "Spravne riesenie");
			std::cout << x;
		}
		REQUIRE("Spravne riesenie" == "Spravne riesenie");
	}
	SECTION("LONG2") {
		for (long x : range(0, 10, -1)) {
			REQUIRE_FALSE("Pozor pretiekol for cyklus" != "Spravne riesenie");
			std::cout << x;
		}
		REQUIRE("Spravne riesenie" == "Spravne riesenie");
	}
	SECTION("LONG3") {
		for (unsigned x : range(90, 50)) {
			REQUIRE_FALSE("Pozor pretiekol for cyklus" != "Spravne riesenie");
			std::cout << x;
		}
		REQUIRE("Spravne riesenie" == "Spravne riesenie");
	}
	SECTION("STRUCT INTEGER") {
		for (Integer x : range(Integer(10), Integer(5), Integer(1))) {
			REQUIRE_FALSE("Pozor pretiekol for cyklus" != "Spravne riesenie");
			std::cout << x;
		}
		REQUIRE("Spravne riesenie" == "Spravne riesenie");
	}
	SECTION("STRUCT INTEGER2") {
		for (Integer x : range(Integer(0), Integer(10), Integer(-1))) {
			REQUIRE_FALSE("Pozor pretiekol for cyklus" != "Spravne riesenie");
			std::cout << x;
		}
		REQUIRE("Spravne riesenie" == "Spravne riesenie");
	}
	SECTION("STRUCT INTEGER3") {
		for (Integer x : range(Integer(0), Integer(10), Integer(-50))) {
			REQUIRE_FALSE("Pozor pretiekol for cyklus" != "Spravne riesenie");
			std::cout << x;
		}
		REQUIRE("Spravne riesenie" == "Spravne riesenie");
	}
	SECTION("STRUCT INTEGER3") {
		for (Integer x : range(Integer(99), Integer(98))) {
			REQUIRE_FALSE("Pozor pretiekol for cyklus" != "Spravne riesenie");
			std::cout << x;
		}
		REQUIRE("Spravne riesenie" == "Spravne riesenie");
	}
}
TEST_CASE("FORWARD_ITERATOR") {
	REQUIRE(typeid(Range<int>::iterator::pointer)==typeid(const int*));
}
