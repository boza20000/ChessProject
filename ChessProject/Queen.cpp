#include "Queen.h"
#include "Board.h"
#include "Rook.h"
#include "Bishop.h"

bool Queen::checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const
{
	//empty place or taking figure
	if (board.getPiece(endX, endY) != nullptr && !isOppositionFigure(board, endX, endY)) {
		return false;
	}
	//use implemented methods of rook and bishop to check if the move is valid
	Rook rook({ startX ,startY }, color);
	if (rook.checkValidMove(board, startX, startY, endX, endY)) {
		return true;
	}
	//use implemented methods of bishop to check if the move is valid
	Bishop bishop({ startX,startY }, color);
	if (bishop.checkValidMove(board, startX, startY, endX, endY)) {
		return true;
	}
	return false;
}

//returns the symbol of the queen based on its color
const wchar_t* Queen::getSymbol() const {
	return (color == Color::WHITE) ? L"♕ " : L"♛ ";
}
//clone method for Queen class
Piece* Queen::clone() const {
	return new Queen(*this);
}