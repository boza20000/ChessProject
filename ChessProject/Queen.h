#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:
	Queen(Position position):Piece(position) {}

	bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
};

