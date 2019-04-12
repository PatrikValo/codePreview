#pragma once

#include "Factory.h"
#include "RandomGenerator.h"
#include "SDLWrapper.h"
#include "Score.h"
#include "Stock.h"
#include "Tetromino.h"
#include "Textures.h"
#include <memory>

class Engine {
	/*Score*/
	Score score_;

	/*Timing*/
	int clock_ = Dimension::CLOCK;
	int rounds_ = 0;
	int ticks_ = 0;

	/*Objects*/
	Stock cubes_;
	std::unique_ptr<ITetromino> actualObject_;
	std::unique_ptr<ITetromino> followingObject_;
	bool isRunning_ = true;

public:
	Engine();

	void gameTick();
	void reset();

	ITetromino *actualObject() { return actualObject_.get(); }
	ITetromino *followingObject() { return followingObject_.get(); }
	bool isRunning() const { return isRunning_; }
	Score const *score() const { return &score_; }

	void renderAll(Renderer &renderer, Textures &textures, ScoreTextures &scoreTextures);

private:
	void switchObjects();
};
