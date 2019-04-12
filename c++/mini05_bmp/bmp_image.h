#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include "bmp/bmp.h"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>

class BMPImage {
	std::string _name;
	std::unique_ptr<Pixel[]> ptr;
	uint16_t _width;
	uint16_t _height;

	void swap(BMPImage& other) {
		using std::swap;
		swap(_width, other._width);
		swap(_height, other._height);
		ptr = std::move(other.ptr);
	}

public:
	BMPImage(const std::string& name)
	    : _name(name) {
		if (!readBMPSize(_name.c_str(), _width, _height)) {
			throw std::runtime_error("Problem readBMPSize");
		}

		ptr = std::make_unique<Pixel[]>(_width * _height);

		if (!readBMP(_name.c_str(), ptr.get())) {
			throw std::runtime_error("Problem readBMP");
		}
	}

	BMPImage(uint16_t width, uint16_t height, const std::string& name = "")
	    : _name(name)
	    , ptr(std::make_unique<Pixel[]>(width * height))
	    , _width(width)
	    , _height(height) {
	}

	BMPImage(const BMPImage& other)
	    : ptr(std::make_unique<Pixel[]>(other._width * other._height))
	    , _width(other._width)
	    , _height(other._height) {
		std::copy(other.ptr.get(), other.ptr.get() + (_width * _height), ptr.get());
	}
	BMPImage& operator=(BMPImage other) {
		swap(other);
		return *this;
	}
	~BMPImage() {
		if (!_name.empty()) {
			if (!writeBMP(_name.c_str(), _width, _height, ptr.get())) {
				std::cerr << "Error while writing file " + _name + "\n";
			}
		}
	}
	uint16_t width() const {
		return _width;
	}
	uint16_t height() const {
		return _height;
	}
	const std::string& filename() const {
		return _name;
	}
	void filename(const std::string& name) {
		_name = name;
	}
	const Pixel& pixel(uint16_t x, uint16_t y) const {
		if (x > _width || y > _height) {
			throw std::out_of_range("Out of range");
		}
		return ptr[(_width * y) + x];
	}
	Pixel& pixel(uint16_t x, uint16_t y) {
		if (x > _width || y > _height) {
			throw std::out_of_range("Out of range");
		}
		return ptr[(_width * y) + x];
	}
};

#endif // BMP_IMAGE_H
