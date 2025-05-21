#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(Position position) :Piece(position) {}
	bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
};

