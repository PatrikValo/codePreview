#include "bmp_image.h"
#include <iostream>

// A very simple demonstration: Read an image and split it into red, green,
// and blue images. Assumes that there is a BMP file named example.bmp in the
// current directory.

void filter(BMPImage& image, uint8_t redF, uint8_t greenF, uint8_t blueF) {
	for (int i = 0; i < image.height(); ++i) {
		for (int j = 0; j < image.width(); ++j) {
			Pixel& p = image.pixel(j, i);
			p.red &= redF;
			p.green &= greenF;
			p.blue &= blueF;
		}
	}
}

int main() {
	BMPImage original("example.bmp");

	// first demo: clone (using the copy construtor), then modify
	// we also have to assign a filename
	BMPImage red = original;
	red.filename("example_red.bmp");
	filter(red, 255, 0, 0);

	// second demo: create new empty image
	BMPImage green(original.width(), original.height(), "example_green.bmp");
	for (int i = 0; i < original.height(); ++i) {
		for (int j = 0; j < original.width(); ++j) {
			green.pixel(j, i).green = original.pixel(j, i).green;
		}
	}

	// third demo: rename and modify
	original.filename("example_blue.bmp");
	filter(original, 0, 0, 255);
}
