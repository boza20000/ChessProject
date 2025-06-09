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
	~Board() = default;
	Board() = default;
	Board(const Board& other);
	void initializeBoard();
	void movePiece(int startX, int startY, int endX, int endY);
	void repaint();
	void printBoard()const;
	void printReverseBoard() const;
	Piece * getPiece(int x, int y) const;
	const wchar_t * getBoard(int x, int y) const;
	void serialiseBoard() const;
	void derialiseBoard() ;
	void makeRokado(Board& board, int kingStartX, int kingStartY, int kingEndX, int kingEndY);
};

