#pragma once
/*Nazov suboru inspirovany hw03*/

struct Position {
	int x;
	int y;
};

bool operator==(const Position& a, const Position& b);
bool operator!=(const Position& a, const Position& b);

struct Vector {
	int x;
	int y;
};

Position& operator+=(Position& position, const Vector& vector);
Position operator+(const Position& position, const Vector& vector);