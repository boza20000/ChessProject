#include "Knight.h"
#include "Board.h"

bool Knight::checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const
{
	if (board.getPiece(endX, endY) != nullptr && !isOppositionFigure(board, endX, endY)) {//empty place
		return false;
	}

	int dx = abs(endX - startX);
	int dy = abs(endY - startY);
	return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

// returns the symbol of the knight based on its color.
const wchar_t* Knight::getSymbol() const
{
	return (color == Color::WHITE) ? L"♘ " : L"♞ ";
}

// This function creates a new instance of Knight and returns a pointer to it.
Piece* Knight::clone() const
{
	return new Knight(*this);
}