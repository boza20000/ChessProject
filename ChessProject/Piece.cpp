#include "Piece.h"
#include "Board.h"
#include "Rook.h"

Piece::Piece(Position position) : position(position), color(Color::WHITE) {}

Piece::Piece(Position position, Color color) : position(position), color(color) {}

void Piece::setPosition(Position newPosition)
{
	position = newPosition;
}

Position Piece::getPosition() const
{
	return position;
}

Color Piece::getColor() const
{
	return color;
}

void Piece::setColor(Color newColor)
{
	color = newColor;
}

bool Piece::isOppositionFigure(const Board& board, int endX, int endY) const
{
	Piece* target = board.getPiece(endX, endY);
	return target != nullptr && target->getColor() != this->color;
}

