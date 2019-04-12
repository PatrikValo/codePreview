#include "bmp.h"
#include <cstdint>
#include <fstream>
#include <iostream>

namespace { // internal implementation stuff
const uint32_t BMP_HEADER_SIZE = 14;
const uint32_t DIB_HEADER_SIZE = 12;
const uint32_t HEADER_SIZE = BMP_HEADER_SIZE + DIB_HEADER_SIZE;
const uint16_t BPP = 24; // bits per pixel

template <typename Integer>
void writeLittleEndian(char* array, Integer num) {
	for (size_t i = 0; i < sizeof(Integer); ++i) {
		array[i] = (num >> (8 * i)) & 0xff;
	}
}

template <typename Integer>
Integer readLittleEndian(const char* array) {
	Integer result{};
	for (size_t i = 0; i < sizeof(Integer); ++i) {
		result |= static_cast<unsigned char>(array[i]) << (8 * i);
	}
	return result;
}

// note: in the following two functions, reinterpret_cast is safe

void writePixel(std::ostream& out, const Pixel& pixel) {
	uint8_t data[] = { pixel.blue, pixel.green, pixel.red };
	out.write(reinterpret_cast<char*>(data), 3);
}

Pixel readPixel(std::istream& in) {
	uint8_t data[3];
	in.read(reinterpret_cast<char*>(data), 3);
	return { data[2], data[1], data[0] };
}

bool readBMPHeader(std::istream& in, char (&header)[HEADER_SIZE]) {
	in.read(header, HEADER_SIZE);
	if (!in || in.gcount() < HEADER_SIZE) {
		return false; // some kind of error while reading header
	}

	// check whether header is correct and supported version
	return header[0] == 'B'
	    && header[1] == 'M'
	    && readLittleEndian<uint32_t>(header + 2) >= HEADER_SIZE
	    && readLittleEndian<uint32_t>(header + 10) == HEADER_SIZE
	    && readLittleEndian<uint32_t>(header + 14) == DIB_HEADER_SIZE
	    && readLittleEndian<uint16_t>(header + 22) == 1
	    && readLittleEndian<uint16_t>(header + 24) == BPP;
}
} // namespace

bool writeBMP(const char* filename, uint16_t width, uint16_t height, const Pixel* pixels) {
	// compute padding (rowSize needs to be a multiple of 4 bytes)
	const uint32_t bytesPerRow = uint32_t(width) * BPP / 8;
	const uint32_t rowPadding = bytesPerRow % 4 == 0 ? 0 : 4 - (bytesPerRow % 4);
	const uint32_t rowSize = bytesPerRow + rowPadding;
	const uint32_t size = rowSize * height;

	char header[HEADER_SIZE] = { 'B', 'M' };
	writeLittleEndian(header + 2, size + HEADER_SIZE); // bmp file size
	// header[6..9] is reserved (zeroes)
	writeLittleEndian(header + 10, HEADER_SIZE); // pixel data offset

	writeLittleEndian(header + 14, DIB_HEADER_SIZE);
	writeLittleEndian(header + 18, width);
	writeLittleEndian(header + 20, height);
	writeLittleEndian(header + 22, uint16_t(1)); // number of color planes
	writeLittleEndian(header + 24, BPP);

	std::ofstream output(filename, std::ios::binary);
	char padding[3] = {};
	output.write(header, sizeof header);
	// note: pixels array is stored "upside down"
	for (int row = height - 1; row >= 0; --row) {
		for (int col = 0; col < width; ++col) {
			writePixel(output, pixels[col + row * width]);
		}
		output.write(padding, rowPadding);
	}

	// true if everything went OK, false otherwise
	return static_cast<bool>(output);
}

bool readBMPSize(const char* filename, uint16_t& width, uint16_t& height) {
	std::ifstream input(filename, std::ios::binary);

	char header[HEADER_SIZE];
	if (!readBMPHeader(input, header)) {
		return false; // problem with input or wrong header
	}

	width = readLittleEndian<uint16_t>(header + 18);
	height = readLittleEndian<uint16_t>(header + 20);

	return true;
}

bool readBMP(const char* filename, Pixel* pixels) {
	std::ifstream input(filename, std::ios::binary);

	char header[HEADER_SIZE];
	if (!readBMPHeader(input, header)) {
		return false; // problem with input or wrong header
	}

	const uint16_t width = readLittleEndian<uint16_t>(header + 18);
	const uint16_t height = readLittleEndian<uint16_t>(header + 20);
	const uint32_t bytesPerRow = uint32_t(width) * BPP / 8;
	const uint32_t rowPadding = bytesPerRow % 4 == 0 ? 0 : 4 - (bytesPerRow % 4);
	char padding[3];

	// note: pixels array is stored "upside down"
	for (int row = height - 1; row >= 0; --row) {
		for (int col = 0; col < width; ++col) {
			pixels[col + row * width] = readPixel(input);
		}
		input.read(padding, rowPadding);
	}

	// true if everything went OK, false otherwise
	return static_cast<bool>(input);
}
