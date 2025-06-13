#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:
	~Queen() = default;
	Queen(Position position):Piece(position) {}
	Queen(Position position, Color color) :Piece(position, color) {}
	bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
	const wchar_t* getSymbol() const override;
	Piece* clone() const override;
};

