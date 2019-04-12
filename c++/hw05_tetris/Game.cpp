#include "Game.h"
#include "Dimension.h"

Game::Game()
    : window_(Dimension::WIDTH, Dimension::HEIGHT)
    , renderer_(*window_.get())
    , textures_(renderer_)
    , scoreTextures_(renderer_) {
}

void Game::handle() {
	SDL_Event event;
	if (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			isRunning_ = false;
			return;
		}

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_UP: {
				engine_.actualObject()->rotateRight();
				break;
			}
			case SDLK_LCTRL: {
				engine_.actualObject()->rotateLeft();
				break;
			}
			case SDLK_DOWN: {
				engine_.actualObject()->down();
				break;
			}
			case SDLK_LEFT: {
				engine_.actualObject()->left();
				break;
			}
			case SDLK_RIGHT: {
				engine_.actualObject()->right();
				break;
			}
			case SDLK_SPACE: {
				engine_.actualObject()->downNow();
				break;
			}
			default:
				break;
			}
		}
	}
}

void Game::update() {

	engine_.gameTick();

	if (!engine_.isRunning()) {
		isRunning_ = false;
		engine_.score()->writeToFile();
	}
}

void Game::render() {
	SDL_Rect info_;
	info_.y = 0;
	info_.x = 0;
	info_.h = Dimension::HEIGHT;
	info_.w = Dimension::WIDTH;
	Surface board{ SDL_LoadBMP("board.bmp") };
	Texture text{ renderer_, board };

	renderer_.clear();

	/*Render background*/
	SDL_RenderCopy(renderer_.get(), text.get(), nullptr, &info_);

	/*Render objects*/
	engine_.renderAll(renderer_, textures_, scoreTextures_);

	if (!isRunning_) {
		/*Render Game Over Window*/
		gameOver();
	}

	renderer_.render();
}

void Game::gameOver() {
	SDL_Rect info_;
	info_.y = 150;
	info_.x = 140;
	info_.h = 300;
	info_.w = 500;
	Surface dialog{ SDL_LoadBMP("dialog.bmp") };
	Texture text{ renderer_, dialog };

	SDL_RenderCopy(renderer_.get(), text.get(), nullptr, &info_);
}

void Game::reset() {
	engine_.reset();
	isRunning_ = true;
}