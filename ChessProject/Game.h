#pragma once
#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "Board.h"
#include "Piece.h"

struct LastMove {
	int startX, startY;
	int endX, endY;
	Piece * movedPiece;
	LastMove(int startX, int startY, int endX, int endY, Piece* movedPiece)
		: startX(startX), startY(startY), endX(endX), endY(endY), movedPiece(movedPiece) {
	}
	~LastMove() = default;
};

enum class GameType
{
	NORMAL,
	BLITZ,
	NO_TIME,
	ADDTIME
};


class Game
{	
public:
	static int counter;
	static GameType type;
	static LastMove lastMove;
	static Color currentPlayer;
	Game() = default;
	~Game() = default;

	void start();
	void end(Color curPlayer);
	void save(Board board);
	void load(Board& board);
	void printChessBoard();
	void gameLoop(Board& board);
	void setupConsole();
	void changeConsoleFont();
	void setGameState(GameType gameType);
	void GameState(int choice);
	GameType getType()const;
	void setTime();

	static void saveGameInFile(const Board board);
	static void loadGameFromFile(Board & board);
	static bool isSquareUnderAttack(const Board& board, int x, int y, Color color);
	static void setColor(int textColor, int bgColor);
	static void cleanConsole();
	static void clearConsoleRow(int row);
	static void moveCursorTo(short x, short y);
	static void loadLastMove(std::wifstream& file);
	static Piece* createPieceFromSymbol(const std::wstring& symbol, Position pos, Color color);
	static void loadCell(std::wifstream& file, Board& board, int col, int row);
};
