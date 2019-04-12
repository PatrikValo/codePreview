#include <iostream>
#include <stdexcept>

#include "Engine.h"
#include "Game.h"
#include <SDL.h>

int main() {
	try {
		Game game{};

		const int FPS = 60;
		const int frameDelay = 1000 / FPS;

		int frameStart;
		int frameTime;
		while (true) {
			while (game.isRunning()) {
				frameStart = SDL_GetTicks();
				game.handle();
				if (!game.isRunning()) {
					return 0;
				}

				game.update();
				game.render();

				frameTime = SDL_GetTicks() - frameStart;

				if (frameDelay > frameTime) {
					SDL_Delay(frameDelay - frameTime);
				}
			}

			SDL_Event event;

			if (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_KEYDOWN) {
					switch (event.key.keysym.sym) {
					case SDLK_n: {
						game.reset();
						break;
					}
					case SDLK_ESCAPE: {
						return 0;
					}
					default:
						break;
					}
				}
				if (event.type == SDL_QUIT) {
					return 0;
				}
			}
		}
	} catch (const std::runtime_error& ex) {
		std::cerr << ex.what();
	}
}
