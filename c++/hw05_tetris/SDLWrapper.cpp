#include "SDLWrapper.h"
#include <stdexcept>
#include <string>

/*SDL*/
SDL::SDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw std::runtime_error(std::string("SDL could not initialize! SDL Error: ") + SDL_GetError() + '\n');
	}
}

SDL::~SDL() {
	SDL_Quit();
}

/*Window*/
Window::Window(int width, int height)
    : window_(SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN)) {
	if (!window_) {
		throw std::runtime_error(std::string("Window could not be created! SDL Error: ") + SDL_GetError() + '\n');
	}
}

Window::~Window() {
	SDL_DestroyWindow(window_);
}

/*Surface*/
Surface::Surface(SDL_Surface* surface)
    : surface_(surface) {
	if (!surface_)
		throw std::runtime_error(std::string("Unable to load surface! SDL Error: ") + SDL_GetError() + '\n');
}

Surface::~Surface() {
	SDL_FreeSurface(surface_);
}

/*Renderer*/
Renderer::Renderer(SDL_Window& window)
    : renderer_(SDL_CreateRenderer(&window, -1, SDL_RENDERER_ACCELERATED)) {
	if (!renderer_)
		throw std::runtime_error(std::string("Cannot create renderer! SDL Error: ") + SDL_GetError() + '\n');
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(renderer_);
}

void Renderer::clear() {
	SDL_RenderClear(renderer_);
}

void Renderer::render() {
	SDL_RenderPresent(renderer_);
}

/*Texture*/
Texture::Texture(Renderer& renderer, Surface& surface)
    : texture_(SDL_CreateTextureFromSurface(renderer.get(), surface.get())) {
	if (!texture_)
		throw std::runtime_error(std::string("CreateTextureFromSurface failed! SDL Error: ") + SDL_GetError() + '\n');
}

Texture::~Texture() {
	SDL_DestroyTexture(texture_);
}