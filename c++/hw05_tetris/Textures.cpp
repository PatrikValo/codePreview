#include "Textures.h"
#include <stdexcept>

Textures::Textures(Renderer& renderer) {
	Surface cyan{ SDL_LoadBMP("cyan.bmp") };
	textures_.emplace(TextureRef::CYAN, std::make_unique<Texture>(renderer, cyan));

	Surface blue{ SDL_LoadBMP("blue.bmp") };
	textures_.emplace(TextureRef::BLUE, std::make_unique<Texture>(renderer, blue));

	Surface orange{ SDL_LoadBMP("orange.bmp") };
	textures_.emplace(TextureRef::ORANGE, std::make_unique<Texture>(renderer, orange));

	Surface yellow{ SDL_LoadBMP("yellow.bmp") };
	textures_.emplace(TextureRef::YELLOW, std::make_unique<Texture>(renderer, yellow));

	Surface green{ SDL_LoadBMP("green.bmp") };
	textures_.emplace(TextureRef::GREEN, std::make_unique<Texture>(renderer, green));

	Surface purple{ SDL_LoadBMP("purple.bmp") };
	textures_.emplace(TextureRef::PURPLE, std::make_unique<Texture>(renderer, purple));

	Surface red{ SDL_LoadBMP("red.bmp") };
	textures_.emplace(TextureRef::RED, std::make_unique<Texture>(renderer, red));
}

Texture& Textures::find(TextureRef type) {
	auto iter = textures_.find(type);
	if (iter == textures_.end()) {
		throw std::runtime_error("Texture is not found");
	}
	return *iter->second;
}

ScoreTextures::ScoreTextures(Renderer& renderer) {
	Surface zero{ SDL_LoadBMP("0.bmp") };
	textures_.emplace(0, std::make_unique<Texture>(renderer, zero));

	Surface one{ SDL_LoadBMP("1.bmp") };
	textures_.emplace(1, std::make_unique<Texture>(renderer, one));

	Surface two{ SDL_LoadBMP("2.bmp") };
	textures_.emplace(2, std::make_unique<Texture>(renderer, two));

	Surface three{ SDL_LoadBMP("3.bmp") };
	textures_.emplace(3, std::make_unique<Texture>(renderer, three));

	Surface four{ SDL_LoadBMP("4.bmp") };
	textures_.emplace(4, std::make_unique<Texture>(renderer, four));

	Surface five{ SDL_LoadBMP("5.bmp") };
	textures_.emplace(5, std::make_unique<Texture>(renderer, five));

	Surface six{ SDL_LoadBMP("6.bmp") };
	textures_.emplace(6, std::make_unique<Texture>(renderer, six));

	Surface seven{ SDL_LoadBMP("7.bmp") };
	textures_.emplace(7, std::make_unique<Texture>(renderer, seven));

	Surface eight{ SDL_LoadBMP("8.bmp") };
	textures_.emplace(8, std::make_unique<Texture>(renderer, eight));

	Surface nine{ SDL_LoadBMP("9.bmp") };
	textures_.emplace(9, std::make_unique<Texture>(renderer, nine));
}

Texture& ScoreTextures::find(int number) {
	auto iter = textures_.find(number);
	if (iter == textures_.end()) {
		throw std::runtime_error("Texture is not found");
	}
	return *iter->second;
}