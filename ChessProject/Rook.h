#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	~Rook() = default;
	Rook(Position position) :Piece(position) {}
	Rook(Position position, Color color) :Piece(position, color) {}
	bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
};

