#include "King.h"
#include "Board.h"
#include "Game.h"


bool King::checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const
{
    //empty place or enemy
	if (board.getPiece(endX, endY) != nullptr && !isOppositionFigure(board, endX, endY)) {
		return false;
	}
    //check for rokado move
	if (rokado(board, startX, startY, endX, endY)) {
		return true;
	}
    //king can move only one square
	if (abs(endX - startX) > 1 || abs(endY - startY) > 1) {
		return false;
	}
	return true;
}

bool King::rokado(const Board& board, int startX, int startY, int endX, int endY) const {
    if (abs(endX - startX) != 2 || startY != endY) return false;
    if (this->getIsMoved()) return false;

    int direction = (endX - startX > 0) ? 1 : -1;
    int rookX = (direction == 1) ? 7 : 0;

    Piece* rook = board.getPiece(rookX, startY);
    if (!rook || rook->getIsMoved()) return false;

    for (int x = startX + direction; x != rookX; x += direction) {
        if (board.getPiece(x, startY) != nullptr) return false;
    }

    for (int offset = 0; offset <= 2; ++offset) {
        int x = startX + direction * offset;
        if (Game::isSquareUnderAttack(board, x, startY, this->getColor())) {
            return false;
        }
    }

    return true;
}

const wchar_t* King::getSymbol() const
{
	return (color == Color::WHITE) ? L"♔ " : L"♚ ";
}

Piece* King::clone() const
{
	return new King(*this);
}
