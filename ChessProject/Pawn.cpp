#include "Pawn.h"
#include "Board.h"
#include "Game.h"

bool Pawn::checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const
{
	int direction = (getColor() == Color::WHITE) ? -1 : 1; // White moves up (row decreases), Black moves down (row increases)
	int startRow = (getColor() == Color::WHITE) ? 6 : 1;   // Starting rows: 6 for White, 1 for Black

	Piece* targetPiece = board.getPiece(endX, endY); // EndX = col, EndY = row

	// Move forward 1 square
	if (endY == startY + direction && endX == startX && targetPiece == nullptr) {
		return true;
	}

	// Move forward 2 squares from starting position
	if (startY == startRow && endY == startY + 2 * direction && endX == startX) {
		Piece* middlePiece = board.getPiece(startX, startY + direction);
		if (middlePiece == nullptr && targetPiece == nullptr) {	 
			return true;
		}
	}

	// Diagonal capture
	if (endY == startY + direction && abs(endX - startX) == 1) {
		if (targetPiece != nullptr && isOppositionFigure(board, endX, endY)) {
			return true;
		}
	}

	if (checkAlPassan())
	{
		LastMove lastMove = Game::lastMove;
	}
	
	return false;
}



bool Pawn::checkAlPassan() const
{
	//if last move was pawn move and the pawn is on the 5th row
	return false;
}

void Pawn::promote() const
{
	std::wcout << L"Pawn promotion! Choose a piece (Q, R, B, K): ";
	wchar_t choice;
	std::wcin >> choice;
	while (true) {
		std::wcin >> choice;
		switch (choice) {
		case L'Q':
		case L'q':
			std::wcout << L"Promoted to Queen!" << std::endl;
			//promote
			return;
		case L'R':
		case L'r':
			std::wcout << L"Promoted to Rook!" << std::endl; \
				//promote
				return;
		case L'B':
		case L'b':
			std::wcout << L"Promoted to Bishop!" << std::endl;
			//promote
			return;
		case L'K':
		case L'k':
			std::wcout << L"Promoted to Knight!" << std::endl;
			//promote
			return;
		default:
			std::wcout << L"Invalid choice. No promotion." << std::endl;
			break;
		}
	}
	//
	//return true;
}

