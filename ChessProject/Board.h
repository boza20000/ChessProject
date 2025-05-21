#pragma once
#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

#include "Piece.h"
class Board
{
private:
	 const wchar_t* board[8][8];
public:
	Board() = default;
	void initializeBoard();
	void setPiece(int x, int y, wchar_t* piece);
	int getPiece(int x, int y);
	void movePiece(int startX, int startY, int endX, int endY);
	void repaint();
	void printBoard()const;
	void printReverseBoard() const;
	Piece * getPiece(int x, int y) const;
	const wchar_t * getBoard(int x, int y) const;
};

