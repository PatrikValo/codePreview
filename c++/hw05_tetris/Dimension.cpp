#include "Dimension.h"

int Dimension::CLOCK = 60;
const int Dimension::PLAYGROUND_W = 510;
const int Dimension::PLAYGROUND_H = 600;
const int Dimension::WIDTH = 770;
const int Dimension::HEIGHT = 600;
const int Dimension::CUBE_SIZE = 30;

const Position Dimension::START_POSITION{ 7, 1 };
const Position Dimension::FOLLOW_POSITION{ Dimension::PLAYGROUND_W / Dimension::CUBE_SIZE + 2, 9 };
const Position Dimension::SCORE_POSITION{ 24 * Dimension::CUBE_SIZE, 3 * Dimension::CUBE_SIZE };

SDL_Rect Dimension::positionToRender(Position position) {
	SDL_Rect rect;
	rect.w = CUBE_SIZE;
	rect.h = CUBE_SIZE;
	rect.x = position.x * CUBE_SIZE;
	rect.y = position.y * CUBE_SIZE;
	return rect;
}

bool Dimension::isValid(Position position) {
	if (position.x < 0 || position.x >= PLAYGROUND_W / CUBE_SIZE) {
		return false;
	}

	return position.y >= 0 && position.y < PLAYGROUND_H / CUBE_SIZE;
}