#pragma once
#include <SDL.h>

/*
 * Nazov suboru a pristupovanie k SDL2 inspirovane hw03 + http://lazyfoo.net/tutorials/SDL/ + videami
 * https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx
 */

class SDL {
public:
	SDL();
	~SDL();
};

class Window {
	SDL_Window *window_;

public:
	Window(int width, int height);
	~Window();

	Window(const Window &) = delete;
	Window &operator=(const Window &) = delete;

	SDL_Window *get() { return window_; }
};

class Surface {
	SDL_Surface *surface_;

public:
	Surface(SDL_Surface *surface);
	~Surface();

	Surface(const Surface &) = delete;
	Surface &operator=(Surface &) = delete;

	SDL_Surface *get() { return surface_; }
};

class Renderer {
	SDL_Renderer *renderer_;

public:
	Renderer(SDL_Window &window);
	~Renderer();

	Renderer(const Renderer &) = delete;
	Renderer &operator=(const Renderer &) = delete;

	void clear();
	void render();
	SDL_Renderer *get() { return renderer_; }
};

class Texture {
	SDL_Texture *texture_;

public:
	Texture(Renderer &renderer, Surface &surface);
	~Texture();

	Texture(const Texture &) = delete;
	Texture &operator=(const Texture &) = delete;

	SDL_Texture *get() { return texture_; }
};
