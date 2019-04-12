#include "Stock.h"

/*Private*/
void Stock::remove(int y) {
	cubes_.erase(std::remove_if(cubes_.begin(), cubes_.end(), [&](Cube cube) {
		return cube.position().y == y;
	}),
	    cubes_.end());
}

void Stock::moveLine(int y, Vector vector) {
	for (auto& cube : cubes_) {
		if (cube.position().y == y) {
			cube.position() += vector;
		}
	}

	auto iter = counter_.find(y);
	if (iter != counter_.end()) {
		counter_[iter->first + vector.y] = iter->second;
		counter_.erase(iter);
	}
}

/*Public*/
void Stock::add(const Cube& cube) {
	counter_[cube.position().y]++;
	cubes_.push_back(cube);
}

int Stock::deleteFullLines() {
	std::vector<int> deletedLine;

	int points = 0;
	// remove cubes from vector
	for (auto& count : counter_) {
		if (count.second == fullLine_) {
			remove(count.first);
			deletedLine.push_back(count.first);
			deleted_ = true;
			points++;
		}
	}

	// update information about cubes in map
	for (auto& line : deletedLine) {
		auto iter = counter_.find(line);
		if (iter != counter_.end()) {
			counter_.erase(iter);
		}
	}
	return points;
}

void Stock::step() {
	// move lines after deleting
	if (deleted_) {
		deleted_ = false;
		int free_lines = 0;
		for (int i = Dimension::PLAYGROUND_H / Dimension::CUBE_SIZE - 1; i >= 0; i--) {
			if (counter_.find(i) == counter_.end()) {
				free_lines++;
			} else {
				if (free_lines != 0) {
					moveLine(i, { 0, free_lines });
				}
			}
		}
	}
}

bool Stock::isOverlap(Position position) {
	for (auto& cube : cubes_) {
		if (cube.position() == position) {
			return true;
		}
	}
	return false;
}

void Stock::render(Renderer& renderer, Textures& textures) {
	SDL_Rect rect;
	for (auto& cube : cubes_) {
		rect = Dimension::positionToRender(cube.position());
		SDL_RenderCopy(renderer.get(), textures.find(cube.texture()).get(), nullptr, &rect);
	}
}