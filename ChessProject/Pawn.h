#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	~Pawn() = default;
	Pawn(Position position):Piece(position) {}
	Pawn(Position position, Color color) :Piece(position, color) {}
	bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
	bool checkAlPassan() const;
	void promote() const;
};

