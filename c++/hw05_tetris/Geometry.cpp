#include "Geometry.h"

bool operator==(const Position& a, const Position& b) {
	return a.x == b.x && a.y == b.y;
}

bool operator!=(const Position& a, const Position& b) {
	return !(a == b);
}

Position& operator+=(Position& position, const Vector& vector) {
	position.x += vector.x;
	position.y += vector.y;
	return position;
}

Position operator+(const Position& position, const Vector& vector) {
	Position p = position;
	p += vector;
	return p;
}