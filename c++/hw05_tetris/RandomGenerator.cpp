#include "RandomGenerator.h"
#include "TextureRef.h"
#include <random>

TextureRef RandomGenerator::generate() {
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, 6);

	return static_cast<TextureRef>(dist(rd));
}
