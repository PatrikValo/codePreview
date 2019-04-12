#pragma once

#include "Cube.h"
#include "Dimension.h"
#include "SDLWrapper.h"
#include "Stock.h"
#include "TextureRef.h"
#include "Textures.h"
#include <iostream>
#include <memory>
#include <vector>

class ITetromino {
public:
	virtual void down() = 0;
	virtual void downNow() = 0;
	virtual void left() = 0;
	virtual void right() = 0;
	virtual void rotateLeft() = 0;
	virtual void rotateRight() = 0;

	/*
	 * breakObject() - break tetromino to cubes and send cubes to stock
	 */
	virtual void breakObject() = 0;

	virtual void moveToStart() = 0;
	virtual void moveToFollow() = 0;

	/*
	 * isOverlap() - check overlapping new position (actual position + vector) with all cubes on stock
	 */
	virtual bool isOverlap(Vector vector) = 0;

	/*
	 * isValid() - check existence new position (actual position + vector) in playground
	 */
	virtual bool isValid(Vector vector) = 0;

	virtual void setEngineCubes(Stock* cubes) = 0;
	virtual bool isMoving() const = 0;

	virtual void render(Renderer& renderer, Textures& textures) = 0;
	virtual ~ITetromino() = default;
};

class Tetromino : public ITetromino {
protected:
	bool isMoving_ = true;
	std::vector<Cube> cubes_;
	Stock* engineCubes_ = nullptr;

public:
	void rotateLeft() override;
	void rotateRight() override;

	void down() override;
	void downNow() override;
	void left() override;
	void right() override;

	void breakObject() override;
	void moveToStart() override;
	void moveToFollow() override;
	void setEngineCubes(Stock* cubes) override { engineCubes_ = cubes; }
	bool isOverlap(Vector vector) override;
	bool isValid(Vector vector) override;

	bool isMoving() const override { return isMoving_; }
	void render(Renderer& renderer, Textures& textures) override;

private:
	void move(Vector vector);
	void moveTo(Position position);
	Vector rotateL(Position middle, Position position);
	Vector rotateR(Position middle, Position position);
};

class TetrominoI : public Tetromino {
public:
	TetrominoI(TextureRef texture);
};

class TetrominoJ : public Tetromino {
public:
	TetrominoJ(TextureRef texture);
};

class TetrominoL : public Tetromino {
public:
	TetrominoL(TextureRef texture);
};

class TetrominoO : public Tetromino {
public:
	TetrominoO(TextureRef texture);

	void rotateLeft() override {}
	void rotateRight() override {}
};

class TetrominoS : public Tetromino {
public:
	TetrominoS(TextureRef texture);
};

class TetrominoT : public Tetromino {
public:
	TetrominoT(TextureRef texture);
};

class TetrominoZ : public Tetromino {
public:
	TetrominoZ(TextureRef texture);
};