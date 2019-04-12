#pragma once

#include "Dimension.h"
#include "SDLWrapper.h"
#include "Textures.h"
#include <SDL.h>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Score {
	// main counter
	int counter_ = 0;

	// points for one deleted line
	int value_ = 40;

	friend Score& operator+=(Score& score, int points);
	friend Score operator+(const Score& score, int points);

public:
	/*
	 * setMiltiple() - increase points for one deleted line
	 */
	void setMultiple(int multiple) { value_ *= multiple; }

	/*
	 * writeToFile() - if score is one of three best results, score is written to file three_best.txt
	 */
	void writeToFile() const;

	/*
	 * render() - function for rendering score
	 */
	void render(Renderer& renderer, ScoreTextures& scoreTextures);
};

Score& operator+=(Score& score, int points);
Score operator+(const Score& score, int points);
