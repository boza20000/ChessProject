#pragma once  
#include <string>  
#include "Board.h" 
#include "Piece.h"

class Commands
{
private:
	std::wstring command;

public:
	Commands() = default;
	Commands(const std::wstring& command);
	~Commands() = default;

	void processCommands(Board& board);
	void setCommand(const std::wstring& command);
	std::wstring getCommand() const;

	bool isValidCommand(Board& board) const;
	static void save(Board& board);
	static void load(Board& board);
	void executeCommand(Board& board,bool isSimulation = false);
	bool isValidMove(const Board& board) const;
	void printHelp();
	void printAvailableCommands();
	void printCurrentCommand();
	void clearCommand();
	bool isPieceProtected(const Board& board, Piece* piece) const;
	Position findKing(const Board& board, Color defender) const;
	bool isPathClear(const Board& board, Color defender, Position* interceptPath, int pathLen)const;
	bool isEscapable(const Board& board, const Position& kingPos, Color defender) const;
	bool isRightColorFigure(const Board& board)const;
	bool moveCorrect(const Board& board, int startX, int startY, int endX, int endY) const;
	bool isCheck(const Board& board , Color color) const;
	bool isFiguirSelected(const Board& board, int x, int y) const;
	bool revailsCheck(const Board& board);
	bool isMate(const Board& board) const;
};