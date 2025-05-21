#include "Piece.h"

Piece::Piece(Position position)
{
	setPosition(position);
}

void Piece::setPosition(Position newPosition)
{
	this->position = newPosition;
}
Position Piece::getPosition() const
{
	return position;
}

