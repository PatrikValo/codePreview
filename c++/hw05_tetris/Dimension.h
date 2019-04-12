#pragma once

#include "Cube.h"
#include <SDL.h>

class Dimension {
public:
	static int CLOCK;
	const static int PLAYGROUND_W;
	const static int PLAYGROUND_H;
	const static int WIDTH;
	const static int HEIGHT;
	const static int CUBE_SIZE;

	const static Position START_POSITION;
	const static Position FOLLOW_POSITION;
	const static Position SCORE_POSITION;

	static SDL_Rect positionToRender(Position position);
	static bool isValid(Position position);
};
