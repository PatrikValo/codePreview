#pragma once

#include <memory>
#include <stdexcept>

#include "Tetromino.h"
#include "TextureRef.h"

/*Princip "Factory" inspirovany z hw03*/

class Factory {
public:
	static std::unique_ptr<ITetromino> tetromino(TextureRef texture) {
		switch (texture) {
		case TextureRef::CYAN:
			return std::make_unique<TetrominoI>(texture);

		case TextureRef::BLUE:
			return std::make_unique<TetrominoJ>(texture);

		case TextureRef::ORANGE:
			return std::make_unique<TetrominoL>(texture);

		case TextureRef::YELLOW:
			return std::make_unique<TetrominoO>(texture);

		case TextureRef::GREEN:
			return std::make_unique<TetrominoS>(texture);

		case TextureRef::PURPLE:
			return std::make_unique<TetrominoT>(texture);

		case TextureRef::RED:
			return std::make_unique<TetrominoZ>(texture);

		default:
			throw std::runtime_error("Out of enum range");
		}
	}
};
