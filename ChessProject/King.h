#pragma once
#include "Piece.h"
#include "String.h"
class King : public Piece
{
public:
	King(Position position) :Piece(position) {}
	bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;

};

