#include "Rook.h"
#include "Board.h"

bool Rook::checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const
{
	// Rook moves either vertically or horizontally
	if (startX != endX && startY != endY) {
		return false;
	}

	// Check for obstacles in vertical movement
	if (startX == endX) {
		int direction = (endY > startY) ? 1 : -1;
		for (int y = startY + direction; y != endY; y += direction) {
			if (board.getPiece(startX, y) != nullptr) {
				return false;
			}
		}
	}
	// Check for obstacles in horizontal movement
	else {
		int direction = (endX > startX) ? 1 : -1;
		for (int x = startX + direction; x != endX; x += direction) {
			if (board.getPiece(x,startY) != nullptr) {
				return false;
			}
		}
	}

	// Block if destination has a same-color piece
	Piece* target = board.getPiece(endX, endY);
	if (target != nullptr && !isOppositionFigure(board, endX, endY)) {
		return false;
	}
	return true;
}

//return the symbol of the rook based on its color
const wchar_t* Rook::getSymbol() const
{
	return (color == Color::WHITE) ? L"♖ " : L"♜ ";
}

//clone function
Piece* Rook::clone() const
{
	return new Rook(*this);
}

