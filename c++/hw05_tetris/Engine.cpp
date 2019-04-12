#include "Engine.h"

Engine::Engine()
    : actualObject_(Factory::tetromino(RandomGenerator::generate()))
    , followingObject_(Factory::tetromino(RandomGenerator::generate())) {

	actualObject_->moveToStart();
	actualObject_->setEngineCubes(&cubes_);
	followingObject_->moveToFollow();
}

void Engine::gameTick() {
	if (ticks_ >= clock_) {
		ticks_ = 0;
		cubes_.step();
		actualObject_->down();
	} else {
		ticks_++;
	}

	if (!actualObject_->isMoving()) {

		switchObjects();

		score_ += cubes_.deleteFullLines();

		if (actualObject_->isOverlap({ 0, 0 })) {
			// game stop
			isRunning_ = false;
			return;
		}

		if (rounds_ == 15) {
			rounds_ = 0;
			if (clock_ > 10) {
				score_.setMultiple(2);
				clock_ -= 10;
			}
		} else {
			rounds_++;
		}
	}
}

void Engine::renderAll(Renderer &renderer, Textures &textures, ScoreTextures &scoreTextures) {
	followingObject_->render(renderer, textures);
	cubes_.render(renderer, textures);
	actualObject_->render(renderer, textures);
	score_.render(renderer, scoreTextures);
}

void Engine::switchObjects() {
	actualObject_->breakObject();

	actualObject_ = std::move(followingObject_);
	actualObject_->setEngineCubes(&cubes_);

	actualObject_->moveToStart();

	followingObject_ = Factory::tetromino(RandomGenerator::generate());
	followingObject_->moveToFollow();
}

void Engine::reset() {
	score_ = Score();
	rounds_ = 0;
	ticks_ = 0;
	clock_ = Dimension::CLOCK;
	cubes_ = Stock();
	actualObject_ = Factory::tetromino(RandomGenerator::generate());
	followingObject_ = Factory::tetromino(RandomGenerator::generate());
	actualObject_->moveToStart();
	actualObject_->setEngineCubes(&cubes_);
	followingObject_->moveToFollow();
	isRunning_ = true;
}