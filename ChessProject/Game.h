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
	static GameType type;
	static LastMove lastMove;
	static Color currentPlayer;
	Game() = default;
	~Game() = default;

	void start();
	void end();
	void save(Board board);
	void load();
	void printChessBoard();
	void gameLoop(Board& board);
	void setupConsole();
	void changeConsoleFont();
	static void saveGameInFile(const Board board);
	static void loadGameFromFile();
	void setGameState(GameType gameType);
	void GameState(int choice);
	GameType getType()const;
	void setTime();
	
	

	static void setColor(int textColor, int bgColor);
	static void cleanConsole();
};
