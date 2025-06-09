#include "Knight.h"
#include "Board.h"

bool Knight::checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const
{
	if (board.getPiece(endX, endY) != nullptr && !isOppositionFigure(board, endX, endY)) {//empty place
		return false;
	}
	int dx = abs(endX - startX);
	int dy = abs(endY - startY);
	// Knight moves in L-shape: 2 by 1 or 1 by 2
	return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}
