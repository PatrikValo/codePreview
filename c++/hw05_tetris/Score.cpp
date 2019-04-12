#include "Score.h"
#include <algorithm>

Score &operator+=(Score &score, int points) {
	score.counter_ += score.value_ * points;
	return score;
}

Score operator+(const Score &score, int points) {
	Score s = score;
	s += score.value_ * points;
	return s;
}

void Score::writeToFile() const {
	std::vector<int> best;
	best.emplace_back(counter_);
	std::ifstream input("three_best.txt");
	if (input) {
		std::string line;
		while (std::getline(input, line)) {
			best.emplace_back(std::stoi(line));
		}
		input.close();
	}
	std::sort(best.begin(), best.end(), std::greater<>());
	std::ofstream output("three_best.txt");
	int numberOf = 0;
	for (int score : best) {
		numberOf++;
		output << score << '\n';
		if (numberOf == 3) {
			break;
		}
	}
}

void Score::render(Renderer &renderer, ScoreTextures &scoreTextures) {
	SDL_Rect info;
	info.w = Dimension::CUBE_SIZE;
	info.h = Dimension::CUBE_SIZE;
	info.y = Dimension::SCORE_POSITION.y;
	info.x = Dimension::SCORE_POSITION.x;
	if (counter_ == 0) {
		// render 0
		SDL_RenderCopy(renderer.get(), scoreTextures.find(0).get(), nullptr, &info);
		return;
	}

	int tmp = counter_;

	while (tmp > 0) {
		SDL_RenderCopy(renderer.get(), scoreTextures.find(tmp % 10).get(), nullptr, &info);
		tmp = tmp / 10;
		info.x -= Dimension::CUBE_SIZE;
	}
}
