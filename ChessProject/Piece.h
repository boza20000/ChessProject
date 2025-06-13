#pragma once
#include <iostream>

enum class Color
{
	WHITE,
	BLACK
};

struct Position
{
	int x;
	int y;
};

class Board;

class Piece
{
protected:
	Position position;
	Color color;
	bool isMoved = false;
public:
	void isMovedToTrue() { isMoved = true; }
	bool getIsMoved() const { return isMoved; }
	Piece(Position position);
	Piece(Position position, Color color);
	virtual ~Piece() = default;
	virtual Piece * clone() const = 0; 
	virtual const wchar_t* getSymbol() const = 0;
	void setPosition(Position newPosition);
	Position getPosition() const;
	Color getColor() const;
	void setColor(Color newColor);
	bool isOppositionFigure(const Board& board, int endX, int endY) const;
	virtual bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const = 0;
};
