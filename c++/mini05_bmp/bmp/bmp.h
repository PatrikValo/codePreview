/// @file bmp.h
#ifndef BMP_H
#define BMP_H

#include <cstddef>
#include <cstdint>

struct Pixel {
	uint8_t red, green, blue;
};

/// Writes an image to a BMP file. The size of the image is given by the
/// parameters width and height, while the contents of the image are given as
/// an array of Pixels. Assumes that the array has length of at least
/// (width * height).
/// Returns true if everything went OK (the file was written correctly),
/// false if an error occurred.
bool writeBMP(const char* filename, uint16_t width, uint16_t height, const Pixel* pixels);

/// Reads a BMP file and returns its width and height (via the two reference
/// parameters).
/// Returns true if everything went OK, false if an error occurred (i.e. the
/// file did not exist or its format was not supported). In the case of an
/// error, the value of the width and height parameters remains unchanged.
bool readBMPSize(const char* filename, uint16_t& width, uint16_t& height);

/// Reads a BMP file and stores its pixel contents in an array of Pixels.
/// Assumes that the pixels parameter points to an array that is large enough
/// (i.e. that has at least width of image * height of image elements).
/// To get the width and the height of an image, use readBMPSize().
/// Returns true if everything went OK, false if an error occurred (i.e. the
/// file did not exist or its format was not supported).
bool readBMP(const char* filename, Pixel* pixels);

#endif // BMP_H
