#pragma once
#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "Board.h"
enum class GameType
{
	NORMAL,
	BLITZ,
	NO_TIME,
	ADDTIME
};


class Game
{
private:
	GameType type;
public:
	Game() = default;
	~Game() = default;
	void start();
	void printChessBoard();
	void end();
	void save();
	void load();
	static void setColor(int textColor, int bgColor);
	static void cleanConsole();
	void setupConsole();
	void changeConsoleFont();
	void gameLoop(Board& board);
	void saveGameInFile();
	void loadGameFromFile();
};

