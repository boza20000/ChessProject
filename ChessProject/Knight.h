#pragma once
	
#include "Piece.h"
#include "String.h"
class Knight : public Piece
{
public:
	Knight(Position position):Piece(position){}
	bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
};

