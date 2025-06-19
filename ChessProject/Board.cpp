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

void Board::free() {
	for (int row = 0; row < 8; ++row)
		for (int col = 0; col < 8; ++col) {
			delete board[row][col];
			board[row][col] = nullptr;
		}
}

void Board::copyFrom(const Board& other) {
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			delete board[row][col];
			if (other.board[row][col] != nullptr) {
				board[row][col] = other.board[row][col]->clone();
				board[row][col]->setPosition({ col, row });
			}
			else {
				board[row][col] = nullptr;
			}
		}
	}
}


Board::~Board() {
	free();
}


Board::Board() {
	for (int row = 0; row < 8; ++row)
		for (int col = 0; col < 8; ++col)
			board[row][col] = nullptr;
}

Board::Board(const Board& other) {
	for (int row = 0; row < 8; ++row)
		for (int col = 0; col < 8; ++col)
			board[row][col] = nullptr;
	copyFrom(other);
}

Board& Board::operator=(const Board& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}
Piece* createBlackPieceForColumn(int row, int col) {
	switch (col) {
	case 0: case 7: return new Rook({ row,col }, Color::BLACK);
	case 1: case 6: return new Knight({ row,col }, Color::BLACK);
	case 2: case 5: return new Bishop({ row,col }, Color::BLACK);
	case 3: return new Queen({ row,col }, Color::BLACK);
	case 4: return new King({ row,col }, Color::BLACK);
	default: return nullptr;
	}
}

Piece* createWhitePieceForColumn(int row, int col) {
	switch (col) {
	case 0: case 7: return new Rook({ row,col }, Color::WHITE);
	case 1: case 6: return new Knight({ row,col }, Color::WHITE);
	case 2: case 5: return new Bishop({ row,col }, Color::WHITE);
	case 3: return new Queen({ row,col }, Color::WHITE);
	case 4: return new King({ row,col }, Color::WHITE);
	default: return nullptr;
	}
}

void Board::initializeBoard()
{
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (row == 1)
				board[row][col] = new Pawn({ row,col }, Color::BLACK);
			else if (row == 6)
				board[row][col] = new Pawn({ row,col }, Color::WHITE);
			else if (row == 0)
				board[row][col] = createBlackPieceForColumn(0, col);
			else if (row == 7)
				board[row][col] = createWhitePieceForColumn(7, col);
			else
				board[row][col] = nullptr;
		}
	}
}
bool Board::checkRokado(int startX, int startY, int endX, int endY) const
{
	Piece* piece = getPiece(startX, startY);
	if (!piece) return false;
	King* king = dynamic_cast<King*>(piece);
	if (!king) return false;
	if (abs(endX - startX) != 2 || startY != endY) return false;
	return king->rokado(*this, startX, startY, endX, endY);
}

void Board::setBoard(int x, int y, Piece* piece)
{
	delete board[y][x];
	board[y][x] = piece;
}

void Board::movePiece(int startX, int startY, int endX, int endY, bool simulate)
{
	bool isRokado = checkRokado(startX, startY, endX, endY);

	makeMove(startX, startY, endX, endY, simulate);

	if (!simulate && isRokado) {
		makeRokado(*this, startX, startY, endX, endY);
	}

	if (!simulate && Pawn::isPromotion(*this)) {
		Pawn::promote(*this);
	}

	if (!simulate) {
		repaint();
	}
}

void Board::repaint()
{
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
			if (board[row][col] != nullptr) {
				std::wcout << board[row][col]->getSymbol();
			}
			else if (board[row][col] == nullptr) {
				std::wcout << L"  ";
			}
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
			if (board[row][col] != nullptr) {
				std::wcout << board[row][col]->getSymbol();
			}
			else if (board[row][col] == nullptr) {
				std::wcout << L"  ";
			}
		}
		Game::setColor(15, 0);
		std::wcout << std::endl;
	}
	std::wcout << L"  h g f e d c b a\n";
}



Piece* Board::getPiece(int x, int y) const
{
	if (x < 0 || x > 7 || y < 0 || y > 7) return nullptr;
	return board[y][x];
}

const wchar_t* Board::getBoard(int x, int y) const
{
	if (board[y][x] != nullptr) {
		return board[y][x]->getSymbol();
	}
	return L"  ";
}

void Board::makeMove(int startX, int startY, int endX, int endY, bool simulate)
{
	delete board[endY][endX];
	board[endY][endX] = board[startY][startX];
	board[startY][startX] = nullptr;

	if (board[endY][endX] != nullptr)
		board[endY][endX]->setPosition({ endX, endY });

	if (!simulate) {
		Game::lastMove = LastMove(startX, startY, endX, endY, board[endY][endX]);
		board[endY][endX]->setMovedToTrue();
	}
}

void Board::makeRokado(Board& board, int kingStartX, int kingStartY, int kingEndX, int kingEndY)
{
	int direction = (kingEndX > kingStartX) ? 1 : -1;
	int rookStartX = (direction == 1) ? 7 : 0;
	int rookStartY = kingStartY;
	int rookEndX = (direction == 1) ? kingEndX - 1 : kingEndX + 1;
	int rookEndY = kingEndY;
	board.makeMove(rookStartX, rookStartY, rookEndX, rookEndY,false);
}
