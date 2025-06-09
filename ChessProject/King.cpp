#include "King.h"
#include "Board.h"

bool King::isRokado = false;

bool King::checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const
{
	if (board.getPiece(endX, endY) != nullptr && !isOppositionFigure(board, endX, endY)) {//empty place or enemy
		return false;
	}
	if (rokado(board, startX, startY, endX, endY)) {
		isRokado = true;
		return true;
	}
	if (abs(endX - startX) > 1 || abs(endY - startY) > 1) {//king can move only one square
		return false;
	}
	return true;
}

bool King::rokado(const Board& board, int startX, int startY, int endX, int endY) const
{
	int direction = (endX - startX > 0) ? 1 : -1;
	if (abs(endX - startX) != 2 || startY != endY) return false;
	if (this->getIsMoved()) return false;

	int rookX = (direction == 1) ? 7 : 0;
	Piece* rook = board.getPiece(rookX, startY);
	if (!rook || rook->getIsMoved()) return false;

	// Check if the path is free
	for (int x = startX + direction; x != rookX; x += direction) {
		if (board.getPiece(x, startY) != nullptr) return false;
	}
	return true;
}
