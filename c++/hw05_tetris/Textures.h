#pragma once

#include "SDLWrapper.h"
#include "TextureRef.h"
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

/*Koncept textur inšpirovaný hw03*/

/*Textures for Game*/
class Textures {
	std::map<TextureRef, std::unique_ptr<Texture>> textures_;

public:
	Textures(Renderer& renderer);

	Texture& find(TextureRef type);
};

/*Textures for score display*/
class ScoreTextures {
	std::map<int, std::unique_ptr<Texture>> textures_;

public:
	ScoreTextures(Renderer& renderer);

	Texture& find(int number);
};