#pragma once
	
#include "Piece.h"
#include "String.h"
class Knight : public Piece
{
public:
	~Knight() = default;
	Knight(Position position):Piece(position){}
	Knight(Position position, Color color) :Piece(position, color) {}
	bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
	const wchar_t* getSymbol() const override;
	Piece* clone() const override;
};

