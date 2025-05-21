#pragma once
#include "Piece.h"
#include "String.h"
#include <iostream>
class Bishop : public Piece
{
public:
	Bishop(Position position) :Piece(position) {}	
	bool checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
};

