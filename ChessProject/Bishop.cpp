#include "Bishop.h"
#include "Board.h"
bool Bishop::checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const
{
    if (abs(endX - startX) != abs(endY - startY)) {
        return false;
    }
    int offsetX = (endX > startX) ? 1 : -1;
    int offsetY = (endY > startY) ? 1 : -1;
    int steps = abs(endX - startX);

    for (int i = 1; i < steps; ++i) {
        int x = startX + i * offsetX;
        int y = startY + i * offsetY;

        if (board.getPiece(x, y) != nullptr) {
            return false;
        }
    }

    Piece* target = board.getPiece(endX, endY);
    if (target == nullptr || isOppositionFigure(board, endX, endY)) {
        return true;
    }
    return false; 
}

const wchar_t* Bishop::getSymbol() const
{
	return (color == Color::WHITE) ? L"♗ " : L"♝ ";
}
Piece* Bishop::clone() const
{
	return new Bishop(*this);
}