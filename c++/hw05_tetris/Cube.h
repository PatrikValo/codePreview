#pragma once

#include "Geometry.h"
#include "TextureRef.h"

class Cube {

	Position position_;
	TextureRef texture_;

public:
	Cube(TextureRef texture)
	    : Cube(0, 0, texture) {
	}

	Cube(int x, int y, TextureRef texture)
	    : position_({ x, y })
	    , texture_(texture) {
	}

	Position& position() {
		return position_;
	}

	Position position() const {
		return position_;
	}

	TextureRef texture() const {
		return texture_;
	}
};
