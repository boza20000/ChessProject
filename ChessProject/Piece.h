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
	//Color color;

public:
	Piece(Position position);
	void setPosition(Position newPosition);
	Position getPosition() const;
	virtual bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY)const = 0;
	virtual ~Piece() = default;

	//Color getColor() const;
    //void setColor(Color newColor);
    //virtual void move(Position newPosition) = 0;
	//virtual void repaintPiece() const = 0;
};

