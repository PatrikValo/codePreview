#ifndef RANGE_HPP
#define RANGE_HPP

#include <cstddef>
#include <iterator>

/**
 * This class should behave the same way as range() in python.
 * You may assume that T is cheap to copy and behaves like a numeric type,
 * i.e. is default-constructible, can be initialized with an integer using
 * T(num), and supports all the arithmetic operations.
 * You cannot assume that T is a primitive type.
 */

template <typename T>
class Range {

	struct Iterator : public std::iterator<std::forward_iterator_tag, T, std::ptrdiff_t, const T*, const T&> {

		using value_type = T;
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;

		Iterator()
		    : value_(T(0))
		    , step_(T(1)) {}

		Iterator(T value, T step)
		    : value_(value)
		    , step_(step) {}

		Iterator& operator++() {
			value_ += step_;
			return *this;
		}

		Iterator operator++(int) {
			Iterator iter(*this);
			value_ += step_;
			return iter;
		}

		Iterator& operator--() {
			value_ -= step_;
			return *this;
		}

		Iterator operator--(int) {
			Iterator iter(*this);
			value_ -= step_;
			return iter;
		}

		T& operator*() {
			return value_;
		}
		const T& operator*() const {
			return value_;
		}

		T* operator->() {
			return &value_;
		}
		const T* operator->() const {
			return &value_;
		}

		bool operator==(const Iterator& r) const {
			return value_ == r.value_;
		}

		bool operator!=(const Iterator& r) const {
			return !(*this == r);
		}

	private:
		friend Range;
		T value_;
		T step_;
	};

public:
	using iterator = Iterator;
	using const_iterator = Iterator;
	Range(T from, T to, T step)
	    : from_(from)
	    , to_(to)
	    , step_(step) {

		if (step == T(0)) {
			throw std::invalid_argument("Step is 0");
		}

		if ((from_ < to_ && step_ < T(0)) || (from_ > to_ && step_ > T(0))) {
			to_ = from_;

		} else {
			T tmp = from_;
			if (from_ < to_) {
				while (tmp + step_ < to_) {
					tmp += step_;
				}
				to_ = tmp + step_;
			} else {
				if (from != to) {
					while (tmp + step_ > to_) {
						tmp += step_;
					}
					to_ = tmp + step_;
				}
			}
		}
	}

	iterator begin() const {
		return iterator(from_, step_);
	}
	iterator end() const {
		return iterator(to_, step_);
	}

private:
	T from_;
	T to_;
	T step_;
};

template <typename T>
auto range(T from, T to, T step) {
	return Range<T>(from, to, step);
}

template <typename T>
auto range(T from, T to) {
	return Range<T>(from, to, T(1));
}

template <typename T>
auto range(T to) {
	return Range<T>(T(0), to, T(1));
}

#endif // RANGE_HPP
