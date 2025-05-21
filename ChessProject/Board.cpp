#include "Board.h"
#include "Game.h"
#include "Symbols.h"
#include "Commands.h"
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"

void Board::initializeBoard()
{
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (row == 1)
				board[row][col] = whitePawn;              
			else if (row == 6)
				board[row][col] = blackPawn;              
			else if (row == 0)
				board[row][col] = whitePieces[col];       
			else if (row == 7)
				board[row][col] = blackPieces[col];       
			else
				board[row][col] = L"  ";                 
		}
	}
}

void Board::setPiece(int x, int y, wchar_t* piece)
{
}

void Board::movePiece(int startX, int startY, int endX, int endY)
{
	this->board[endY][endX] = this->board[startY][startX];
	this->board[startY][startX] = L"  ";
	repaint();
}

void Board::repaint()
{
	//use cursor to repaint the two places where the change happened
	Game::cleanConsole();
	printBoard();
	std::wcout << L"\n";
	printReverseBoard();
}
void Board::printBoard() const
{
	_setmode(_fileno(stdout), _O_U16TEXT); // Enable UTF-16 output

	for (int row = 7; row >= 0; row--) {
		std::wcout << (row + 1) << L" ";  
		for (int col = 0; col < 8; col++) {
			bool isWhiteSquare = (row + col) % 2 == 0;
			Game::setColor(row < 2 || row > 5 ? 15 : 8, isWhiteSquare ? 8 : 4);

			std::wcout << board[row][col];
		}
		Game::setColor(15, 0);
		std::wcout << std::endl;
	}
	std::wcout << L"  a b c d e f g h\n";
}

void Board::printReverseBoard() const
{
	_setmode(_fileno(stdout), _O_U16TEXT); // Enable UTF-16 output

	for (int row = 0; row < 8; row++) {
		std::wcout << (row + 1) << L" ";
		for (int col = 7; col >= 0; col--) {
			bool isWhiteSquare = (row + col) % 2 == 0;
			Game::setColor(row < 2 || row > 5 ? 15 : 8, isWhiteSquare ? 8 : 4);

			std::wcout << board[row][col];
		}
		Game::setColor(15, 0);
		std::wcout << std::endl;
	}
	std::wcout << L"  h g f e d c b a\n";
}

Piece* Board::getPiece(int x, int y) const
{
	const wchar_t * symbol = board[y][x];

	if (symbol == L"♜ " || symbol == L"♖ ") {
		return new Rook({ x, y });
	}
	else if (symbol == L"♞ " || symbol == L"♘ ") {
		return new Knight({ x, y });
	}
	else if (symbol == L"♟ " || symbol == L"♙ ") {
		return new Pawn({ x, y });
	}
	else if (symbol == L"♗ " || symbol == L"♝ ") {
		return new Bishop({ x, y });
	}
	else if (symbol == L"♕ " || symbol == L"♛ ") {
		return new Queen({ x, y });
	}
	else if (symbol == L"♔ " || symbol == L"♚ ") {
		return new King({ x, y });
	}

	return nullptr;
}

const wchar_t* Board::getBoard(int x, int y) const
{
	return board[x][y];
}
