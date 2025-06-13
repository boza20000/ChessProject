#pragma once
#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

#include "Piece.h"
class Board
{
private:
	void copyFrom(const Board& other);
	void free();
	Piece * board[8][8];
public:
	~Board();
	Board();
	Board(const Board& other);
	Board& operator=(const Board& other);
	void initializeBoard();
	void movePiece(int startX, int startY, int endX, int endY, bool isSimulation);
	void repaint();
	void printBoard()const;
	void printReverseBoard() const;
	Piece* getPiece(int x, int y) const;
	const wchar_t* getBoard(int x, int y) const;
	void makeMove(int startX, int startY, int endX, int endY , bool isSimulation);
	void makeRokado(Board& board, int kingStartX, int kingStartY, int kingEndX, int kingEndY);
	bool checkRokado(int startX, int startY, int endX, int endY) const;
	void setBoard(int x, int y, Piece * value);
};

