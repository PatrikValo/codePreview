#pragma once

#include "Cube.h"
#include "Dimension.h"
#include "SDLWrapper.h"
#include "Textures.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

class Stock {
	bool deleted_ = false;

	int fullLine_ = Dimension::PLAYGROUND_W / Dimension::CUBE_SIZE;
	std::vector<Cube> cubes_;
	std::map<int, int> counter_;

	void remove(int y);
	void moveLine(int y, Vector vector);

public:
	/*
	 * add(Cube) - add cube to stock
	 */
	void add(const Cube &cube);

	/*
	 * deleteFullLInes() - delete full lines
	 */
	int deleteFullLines();

	/*
	 * step() - move all lines over deleted lines
	 */
	void step();

	/*
	 * isOverlap(Position) - check existence of cube on position
	 */
	bool isOverlap(Position position);

	/*
	 * render() - render all cubes
	 */
	void render(Renderer &renderer, Textures &textures);
};
