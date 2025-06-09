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
//#include <cwchar> 

Board::Board(const Board& other)
{
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			board[row][col] = other.board[row][col];
		}
	}
}

void Board::initializeBoard()
{
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (row == 1)
				board[row][col] = blackPawn;
			else if (row == 6)
				board[row][col] = whitePawn;
			else if (row == 0)
				board[row][col] = blackPieces[col];
			else if (row == 7)
				board[row][col] = whitePieces[col];
			else
				board[row][col] = L"  ";
		}
	}
}

void Board::movePiece(int startX, int startY, int endX, int endY)
{
	this->board[endY][endX] = this->board[startY][startX];
	this->board[startY][startX] = L"  ";
	Piece* movedPiece = getPiece(endX, endY);
	Game::lastMove = LastMove(startX, startY, endX, endY, movedPiece);
	movedPiece->isMovedToTrue();
	if (King::isRokado) {
		King::isRokado = false;
		makeRokado(*this, startX, startY, endX, endY);
	}
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
	for (int row = 0; row < 8; row++) {
		std::wcout << (8 - row) << L" ";
		for (int col = 0; col < 8; col++) {
			bool isWhiteSquare = (row + col) % 2 == 0;
			Game::setColor(row < 2 || row > 5 ? 15 : 0, isWhiteSquare ? 4 : 1);
			std::wcout << board[row][col];
		}
		Game::setColor(15, 0);
		std::wcout << std::endl;
	}
	std::wcout << L"  a b c d e f g h\n";
}

void Board::printReverseBoard() const
{
	for (int row = 7; row >= 0; row--) {
		std::wcout << (8 - row) << L" ";
		for (int col = 7; col >= 0; col--) {
			bool isWhiteSquare = (row + col) % 2 == 0;
			Game::setColor(row < 2 || row > 5 ? 15 : 0, isWhiteSquare ? 4 : 1);
			std::wcout << board[row][col];
		}
		Game::setColor(15, 0);
		std::wcout << std::endl;
	}
	std::wcout << L"  h g f e d c b a\n";
}


Piece* Board::getPiece(int x, int y) const
{
	const wchar_t* symbol = board[y][x];
	//Position position = { y,x };
	if (std::wcscmp(symbol, L"♜ ") == 0)
		return new Rook({ x, y }, Color::WHITE);
	else if (std::wcscmp(symbol, L"♖ ") == 0)
		return new Rook({ x, y }, Color::BLACK);
	else if (std::wcscmp(symbol, L"♞ ") == 0)
		return new Knight({ x, y }, Color::WHITE);
	else if (std::wcscmp(symbol, L"♘ ") == 0)
		return new Knight({ x, y }, Color::BLACK);
	else if (std::wcscmp(symbol, L"♟") == 0)
		return new Pawn({ x, y }, Color::WHITE);
	else if (std::wcscmp(symbol, L"♙ ") == 0)
		return new Pawn({ x, y }, Color::BLACK);
	else if (std::wcscmp(symbol, L"♝ ") == 0)
		return new Bishop({ x, y }, Color::WHITE);
	else if (std::wcscmp(symbol, L"♗ ") == 0)
		return new Bishop({ x, y }, Color::BLACK);
	else if (std::wcscmp(symbol, L"♛ ") == 0)
		return new Queen({ x, y }, Color::WHITE);
	else if (std::wcscmp(symbol, L"♕ ") == 0)
		return new Queen({ x, y }, Color::BLACK);
	else if (std::wcscmp(symbol, L"♚ ") == 0)
		return new King({ x, y }, Color::WHITE);
	else if (std::wcscmp(symbol, L"♔ ") == 0)
		return new King({ x, y }, Color::BLACK);

	return nullptr;
}


const wchar_t* Board::getBoard(int x, int y) const
{
	return board[y][x];
}

void Board::serialiseBoard() const
{
}

void Board::derialiseBoard()
{
}

void Board::makeRokado(Board& board, int kingStartX, int kingStartY, int kingEndX, int kingEndY)
{
	int direction = (kingEndX > kingStartX) ? 1 : -1;
	int rookStartX = (direction == 1) ? 7 : 0;
	int rookStartY = kingStartY;
	int rookEndX = (direction == 1) ? kingEndX - 1 : kingEndX + 1;
	int rookEndY = kingEndY;
	board.movePiece(rookStartX, rookStartY, rookEndX, rookEndY);
}
