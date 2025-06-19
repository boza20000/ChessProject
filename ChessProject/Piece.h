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
	void setMovedToTrue();
	bool getIsMoved() const;
	bool isOppositionFigure(const Board& board, int endX, int endY) const;
	void setPosition(Position newPosition);
	void setColor(Color newColor);
	Piece(Position position);
	Piece(Position position, Color color);
	Position getPosition() const;
	Color getColor() const;

	
	virtual bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const = 0;
	virtual ~Piece() = default;
	virtual Piece* clone() const = 0;
	virtual const wchar_t* getSymbol() const = 0;
};
