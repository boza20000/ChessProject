#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	Pawn(Position position):Piece(position) {}
	bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
};

