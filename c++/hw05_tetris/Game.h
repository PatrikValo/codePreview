#pragma once

#include "Engine.h"
#include "Tetromino.h"
#include "Textures.h"
#include <memory>
#include <vector>

class Game {
	SDL sdl_;
	Window window_;
	Renderer renderer_;
	Textures textures_;
	ScoreTextures scoreTextures_;
	Engine engine_;
	bool isRunning_{ true };

	void gameOver();

public:
	Game();

	void handle();
	void update();
	void render();
	void reset();

	bool isRunning() const { return isRunning_; }
};