#pragma once
#include "Piece.h"
#include "Board.h"
class King : public Piece
{
public:
	~King() = default;
	King(Position position) :Piece(position) {}
	King(Position position, Color color) :Piece(position, color) {}
	bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
	bool rokado(const Board& board, int startX, int startY, int endX, int endY) const;
	const wchar_t* getSymbol() const override;
	Piece* clone() const override;
};

