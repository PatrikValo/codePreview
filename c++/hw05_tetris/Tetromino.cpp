#include "Tetromino.h"
#include "Game.h"

void Tetromino::down() {
	if (isOverlap({ 0, 1 }) || !isValid({ 0, 1 })) {
		isMoving_ = false;
		return;
	}
	move({ 0, 1 });
}

void Tetromino::downNow() {
	while (!isOverlap({ 0, 1 }) && isValid({ 0, 1 })) {
		move({ 0, 1 });
	}
	isMoving_ = false;
}

void Tetromino::left() {
	if (isOverlap({ -1, 0 }) || !isValid({ -1, 0 })) {
		return;
	}
	move({ -1, 0 });
}

void Tetromino::right() {
	if (isOverlap({ 1, 0 }) || !isValid({ 1, 0 })) {
		return;
	}

	move({ 1, 0 });
}

void Tetromino::rotateLeft() {
	for (auto& cube : cubes_) {
		Vector vector = rotateL(cubes_[1].position(), cube.position());
		if (engineCubes_->isOverlap(cube.position() + vector) || !Dimension::isValid(cube.position() + vector)) {
			return;
		}
	}

	for (auto& cube : cubes_) {
		cube.position() += rotateL(cubes_[1].position(), cube.position());
	}
}

void Tetromino::rotateRight() {
	for (auto& cube : cubes_) {
		Vector vector = rotateR(cubes_[1].position(), cube.position());
		if (engineCubes_->isOverlap(cube.position() + vector) || !Dimension::isValid(cube.position() + vector)) {
			return;
		}
	}

	for (auto& cube : cubes_) {
		cube.position() += rotateR(cubes_[1].position(), cube.position());
	}
}

void Tetromino::breakObject() {
	for (auto& cube : cubes_) {
		engineCubes_->add(cube);
	}
	cubes_.clear();
}

void Tetromino::moveToStart() {
	moveTo(Dimension::START_POSITION);
}

void Tetromino::moveToFollow() {
	moveTo(Dimension::FOLLOW_POSITION);
}

bool Tetromino::isOverlap(Vector vector) {
	for (auto& cube : cubes_) {
		if (engineCubes_->isOverlap(cube.position() + vector)) {
			return true;
		}
	}
	return false;
}

bool Tetromino::isValid(Vector vector) {
	for (auto& cube : cubes_) {
		if (!Dimension::isValid(cube.position() + vector)) {
			return false;
		}
	}
	return true;
}

void Tetromino::render(Renderer& renderer, Textures& textures) {
	SDL_Rect rect;
	for (int i = 0; i < 4; i++) {
		rect = Dimension::positionToRender(cubes_[i].position());
		SDL_RenderCopy(renderer.get(), textures.find(cubes_[i].texture()).get(), nullptr, &rect);
	}
}

void Tetromino::move(Vector vector) {
	for (auto& cube : cubes_) {
		cube.position() += vector;
	}
}

void Tetromino::moveTo(Position position) {
	int minX = Dimension::WIDTH;
	int minY = Dimension::HEIGHT;
	for (auto& cube : cubes_) {
		if (cube.position().x < minX) {
			minX = cube.position().x;
		}

		if (cube.position().y < minY) {
			minY = cube.position().y;
		}
	}

	for (auto& cube : cubes_) {
		cube.position().x = position.x + abs(minX - cube.position().x);
		cube.position().y = position.y + abs(minY - cube.position().y);
	}
}

Vector Tetromino::rotateL(Position middle, Position position) {
	if (middle.y < position.y) {
		if (middle.x > position.x) {
			return { 2, 0 };
		}

		if (middle.x == position.x) {
			return { 1 * (position.y - middle.y), -1 * (position.y - middle.y) };
		}

		if (middle.x < position.x) {
			return { 0, -2 };
		}
	}

	if (middle.y == position.y) {
		if (middle.x > position.x) {
			return { 1 * (middle.x - position.x), 1 * (middle.x - position.x) };
		}

		if (middle.x < position.x) {
			return { -1 * (position.x - middle.x), -1 * (position.x - middle.x) };
		}

		return { 0, 0 };
	}

	if (middle.y > position.y) {
		if (middle.x > position.x) {
			return { 0, 2 };
		}

		if (middle.x == position.x) {
			return { -1 * (middle.y - position.y), 1 * (middle.y - position.y) };
		}

		if (middle.x < position.x) {
			return { -2, 0 };
		}
	}
	return { 0, 0 };
}

Vector Tetromino::rotateR(Position middle, Position position) {
	if (middle.y < position.y) {
		if (middle.x > position.x) {
			return { 0, -2 };
		}

		if (middle.x == position.x) {
			return { -1 * (position.y - middle.y), -1 * (position.y - middle.y) };
		}

		if (middle.x < position.x) {
			return { -2, 0 };
		}
	}

	if (middle.y == position.y) {
		if (middle.x > position.x) {
			return { 1 * (middle.x - position.x), -1 * (middle.x - position.x) };
		}

		if (middle.x < position.x) {
			return { -1 * (position.x - middle.x), 1 * (position.x - middle.x) };
		}
		return { 0, 0 };
	}

	if (middle.y > position.y) {
		if (middle.x > position.x) {
			return { 2, 0 };
		}

		if (middle.x == position.x) {
			return { 1 * (middle.y - position.y), 1 * (middle.y - position.y) };
		}

		if (middle.x < position.x) {
			return { 0, 2 };
		}
	}
	return { 0, 0 };
}

TetrominoI::TetrominoI(TextureRef texture) {
	for (int i = 0; i < 4; i++) {
		cubes_.emplace_back(i, 0, texture);
	}
}

TetrominoJ::TetrominoJ(TextureRef texture) {
	for (int i = 0; i < 3; i++) {
		cubes_.emplace_back(i, 0, texture);
	}
	cubes_.emplace_back(2, 1, texture);
}

TetrominoL::TetrominoL(TextureRef texture) {
	for (int i = 0; i < 3; i++) {
		cubes_.emplace_back(i, 0, texture);
	}
	cubes_.emplace_back(0, 1, texture);
}

TetrominoO::TetrominoO(TextureRef texture) {
	cubes_.emplace_back(0, 0, texture);
	cubes_.emplace_back(1, 0, texture);
	cubes_.emplace_back(0, 1, texture);
	cubes_.emplace_back(1, 1, texture);
}

TetrominoS::TetrominoS(TextureRef texture) {
	cubes_.emplace_back(0, 1, texture);
	cubes_.emplace_back(1, 1, texture);
	cubes_.emplace_back(1, 0, texture);
	cubes_.emplace_back(2, 0, texture);
}

TetrominoT::TetrominoT(TextureRef texture) {
	for (int i = 0; i < 3; i++) {
		cubes_.emplace_back(i, 0, texture);
	}
	cubes_.emplace_back(1, 1, texture);
}

TetrominoZ::TetrominoZ(TextureRef texture) {
	cubes_.emplace_back(0, 0, texture);
	cubes_.emplace_back(1, 0, texture);
	cubes_.emplace_back(1, 1, texture);
	cubes_.emplace_back(2, 1, texture);
}