#include "Pawn.h"
#include "Board.h"
#include "Game.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"

bool Pawn::checkValidMove(const Board& board, int startX, int startY, int endX, int endY) const
{
	int direction = (getColor() == Color::WHITE) ? -1 : 1; // White moves up (row decreases), Black moves down (row increases)
	int startRow = (getColor() == Color::WHITE) ? 6 : 1;   // Starting rows: 6 for White, 1 for Black

	Piece* targetPiece = board.getPiece(endX, endY);

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

	/*if (checkAlPassan())
	{
		LastMove lastMove = Game::lastMove;
	}*/

	return false;
}



bool Pawn::checkAlPassan() const {
	//LastMove lastMove = Game::lastMove;
	//if (!lastMove.movedPiece || lastMove.movedPiece->getType() != PieceType::PAWN)
	//	return false;

	//int direction = (getColor() == Color::WHITE) ? -1 : 1;
	//int currentY = (getColor() == Color::WHITE) ? 3 : 4; // Row 5 for white, 4 for black

	//// Must be on the correct row to perform en passant
	//if (Game::selectedY != currentY)
	//	return false;

	//// The last move must have been a 2-step pawn advance
	//if (abs(lastMove.endY - lastMove.startY) == 2 &&
	//	lastMove.endY == Game::selectedY &&
	//	abs(lastMove.endX - Game::selectedX) == 1)
	//{
	//	return true;
	//}

	return false;
}

bool Pawn::isPromotion(const Board& board)
{
	const wchar_t* piece = board.getBoard(Game::lastMove.endX, Game::lastMove.endY);

	if ((Game::lastMove.endY == 7 && Game::lastMove.movedPiece->getColor() == Color::BLACK && L"♟" == piece))
	{
		return true;
	}
	if ((Game::lastMove.endY == 0 && Game::lastMove.movedPiece->getColor() == Color::WHITE) &&  L"♙ " == piece)
	{
		return true;
	}
	return false;
}

void Pawn::makePromotion(Board& board, char obj)
{
	if (obj == 'q') { 
		Piece* p = new Queen({ Game::lastMove.endX, Game::lastMove.endY }, Game::currentPlayer);
		board.setBoard(Game::lastMove.endX, Game::lastMove.endY, p);
	}
	else if (obj == 'r') {
		board.setBoard(Game::lastMove.endX, Game::lastMove.endY,
			new Rook({ Game::lastMove.endX, Game::lastMove.endY }, Game::currentPlayer));
	}
	else if (obj == 'b') {
		board.setBoard(Game::lastMove.endX, Game::lastMove.endY,
			new Bishop({ Game::lastMove.endX, Game::lastMove.endY }, Game::currentPlayer));
	}
	else if (obj == 'k') {
		board.setBoard(Game::lastMove.endX, Game::lastMove.endY,
			new Knight({ Game::lastMove.endX, Game::lastMove.endY }, Game::currentPlayer));
	}
}

void Pawn::promote(Board& board)
{
	Game::moveCursorTo(0, 21);
	std::wcout << L"Pawn promotion! Choose a piece Q(Queen), R(Rook), B(Bishop), K(Knight): ";
	Game::moveCursorTo(0, 20);
	Game::clearConsoleRow(20);

	wchar_t choice;
	char obj;

	while (true) {
		Game::moveCursorTo(0, 20);
		std::wcout << L"Promote to: ";
		std::wcin >> choice;

		std::wcin.clear();
		std::wcin.ignore(1000, '\n');

		switch (choice) {
		case L'Q': case L'q': obj = 'q'; break;
		case L'R': case L'r': obj = 'r'; break;
		case L'B': case L'b': obj = 'b'; break;
		case L'K': case L'k': obj = 'k'; break;

		default:
			Game::clearConsoleRow(20);
			continue;
		}

		makePromotion(board, obj);
		Game::clearConsoleRow(20);
		Game::clearConsoleRow(21);

		break;
	}
}

const wchar_t* Pawn::getSymbol() const
{
	return (color == Color::WHITE) ? L"♙ " : L"♟";
}

Piece* Pawn::clone() const
{
	return new Pawn(*this);
}