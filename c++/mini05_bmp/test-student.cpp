#include "catch.hpp"

#include "bmp_image.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

// This is here so that we can compare Pixels using the ==/!= operators.
inline bool operator==(const Pixel& a, const Pixel& b) {
	return a.red == b.red && a.green == b.green && a.blue == b.blue;
}

inline bool operator!=(const Pixel& a, const Pixel& b) {
	return !(a == b);
}

// This is here so that we can output Pixels with the << operator.
inline std::ostream& operator<<(std::ostream& out, const Pixel& p) {
	return out << "{" << int(p.red) << ", " << int(p.green) << ", "
	           << int(p.blue) << "}";
}

namespace {
void cloneExample() {
	const int size = 1577498;

	static bool cloned = false;
	static char buffer[size];

	if (!cloned) {
		std::ifstream in("example.bmp", std::ios::binary);
		if (!in) {
			std::cerr << "Could not open example.bmp. Are you "
			             "running the tests in the correct working"
			             " directory?\n";
			std::exit(1);
		}
		in.read(buffer, size);
		cloned = true;
	}
	std::ofstream out("example_aux.bmp", std::ios::binary);
	out.write(buffer, size);
}

void checkExamplePixels(const BMPImage& image) {
	struct PixelProbe {
		uint16_t x, y;
		Pixel pixel;
	};
	static const PixelProbe pixelProbes[] = {
		{ 0, 0, { 34, 125, 221 } },
		{ 0, 1, { 36, 129, 224 } },
		{ 1, 0, { 38, 128, 224 } },
		{ 1, 1, { 39, 129, 225 } },
		{ 421, 312, { 136, 128, 174 } },
		{ 841, 623, { 5, 18, 6 } },
		{ 17, 42, { 38, 131, 227 } }
	};
	for (const auto& p : pixelProbes) {
		INFO("pixel() with x = " << p.x << ", y = " << p.y);
		CHECK(p.pixel == image.pixel(p.x, p.y));
	}
}

void checkSmall(std::istream& in) {
	const int size = 74;

	static const char expected[size] = {
		66, 77, 74, 0, 0, 0, 0, 0, 0, 0, 26, 0, 0, 0, 12, 0, 0, 0, 3,
		0, 4, 0, 1, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 120, 76, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	char contents[size];
	in.read(contents, size);
	for (int i = 0; i < size; ++i) {
		INFO("Differs at byte no. " << i);
		REQUIRE(expected[i] == contents[i]);
	}
}
} // namespace

TEST_CASE("Constructor: load existing file") {
	cloneExample();
	const BMPImage image("example_aux.bmp");
	CHECK(842 == image.width());
	CHECK(624 == image.height());
	CHECK("example_aux.bmp" == image.filename());
	checkExamplePixels(image);
}

TEST_CASE("Constructor: load nonexistent file") {
	REQUIRE_THROWS_AS(BMPImage("nonexistent_file.bmp"), std::runtime_error);
}

TEST_CASE("Constructor: new image") {
	const int w = 123;
	const int h = 456;
	const BMPImage image(w, h);
	CHECK(w == image.width());
	CHECK(h == image.height());
	CHECK("" == image.filename());
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			INFO("pixel() with x = " << x << ", y = " << y);
			CHECK(Pixel{ 0, 0, 0 } == image.pixel(x, y));
		}
	}
}

TEST_CASE("Copy constructor: copy image") {
	cloneExample();
	const BMPImage image("example_aux.bmp");
	const BMPImage clone = image;
	REQUIRE(image.width() == clone.width());
	REQUIRE(image.height() == clone.height());
	CHECK("" == clone.filename());
	for (int y = 0; y < clone.height(); ++y) {
		for (int x = 0; x < clone.width(); ++x) {
			INFO("pixel() with x = " << x << ", y = " << y);
			CHECK(image.pixel(x, y) == clone.pixel(x, y));
		}
	}
}

TEST_CASE("Copy assignment: copy image") {
	cloneExample();
	const BMPImage image("example_aux.bmp");
	BMPImage other(10, 10, "temp.bmp");
	other = image;
	REQUIRE(image.width() == other.width());
	REQUIRE(image.height() == other.height());
	CHECK("example_aux.bmp" == image.filename());
	CHECK("temp.bmp" == other.filename());
	for (int y = 0; y < other.height(); ++y) {
		for (int x = 0; x < other.width(); ++x) {
			INFO("pixel() with x = " << x << ", y = " << y);
			CHECK(image.pixel(x, y) == other.pixel(x, y));
		}
	}
}

TEST_CASE("Destructor: write new file") {
	{
		BMPImage image(3, 4, "temp.bmp");
		image.pixel(1, 2) = { 17, 76, 120 };
	}
	std::ifstream in("temp.bmp", std::ios::binary);
	checkSmall(in);
}

TEST_CASE("Destructor: modify file") {
	int originalWidth, originalHeight;
	{
		cloneExample();
		BMPImage image("example_aux.bmp");
		image.pixel(1, 2) = { 17, 76, 120 };
		originalWidth = image.width();
		originalHeight = image.height();
	}

	BMPImage image("example_aux.bmp");
	REQUIRE(originalWidth == image.width());
	REQUIRE(originalHeight == image.height());
	CHECK(Pixel{ 17, 76, 120 } == image.pixel(1, 2));
}

TEST_CASE("pixel: out of range") {
	cloneExample();
	BMPImage image("example_aux.bmp");
	const BMPImage& c_image = image;

	{
		INFO("non-const version");
		CHECK_THROWS_AS(image.pixel(900, 0), std::out_of_range);
		CHECK_THROWS_AS(image.pixel(0, 700), std::out_of_range);
		CHECK_THROWS_AS(image.pixel(900, 700), std::out_of_range);
	}

	{
		INFO("const version");
		CHECK_THROWS_AS(c_image.pixel(900, 0), std::out_of_range);
		CHECK_THROWS_AS(c_image.pixel(0, 700), std::out_of_range);
		CHECK_THROWS_AS(c_image.pixel(900, 700), std::out_of_range);
	}
}

TEST_CASE("pixel: const and non-const versions match") {
	cloneExample();
	BMPImage image("example_aux.bmp");
	const BMPImage& c_image = image;
	for (int y = 0; y < image.height(); ++y) {
		for (int x = 0; x < image.width(); ++x) {
			INFO("pixel with x = " << x << ", y = " << y);
			CHECK(&image.pixel(x, y) == &c_image.pixel(x, y));
		}
	}
}

inline bool is_modifiable(Pixel& /*unused*/) { return true; }
inline bool is_modifiable(const Pixel& /*unused*/) { return false; }

TEST_CASE("pixel: const version does not allow modifying Pixels") {
	cloneExample();
	const BMPImage image("example_aux.bmp");
	REQUIRE_FALSE(is_modifiable(image.pixel(0, 0)));
}

TEST_CASE("filename() as a setter") {
	const char* orig_name = "some-filename.bmp";
	const char* new_name =  "a-different-filename.bmp";
	{
		BMPImage image(10, 10, orig_name);
		REQUIRE(image.filename() == orig_name);
		image.filename(new_name);
		REQUIRE(image.filename() == new_name);
	}
	std::ifstream in(new_name, std::ios::binary);
	REQUIRE(in.good());
}
