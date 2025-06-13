#pragma once
#include "Piece.h"
#include "String.h"
#include <iostream>
class Bishop : public Piece
{
public:
	~Bishop() = default;
	Bishop(Position position,Color color) :Piece(position,color) {}	
	Bishop(Position position) :Piece(position) {}
	bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
	const wchar_t* getSymbol() const override;
	Piece* clone() const override;
};

