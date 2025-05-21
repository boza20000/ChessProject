#include "Commands.h"
#include <iostream>
#include "Board.h"

const int MAX_COMMAND_LENGTH = 6;

Commands::Commands(const std::wstring& command)
{
	setCommand(command);
}

void Commands::processCommands(Board& board)
{
	std::wcin.clear();
	wchar_t inputBuffer[MAX_COMMAND_LENGTH];
	std::wcin.getline(inputBuffer, MAX_COMMAND_LENGTH);
	setCommand(std::wstring(inputBuffer));
	if (isValidCommand() && isValidMove(board)) {
		executeCommand(board);
	}
	else {
		throw std::invalid_argument("Invalid move");
	}
}

void Commands::setCommand(const std::wstring& command)
{
	this->command = command;
}

std::wstring Commands::getCommand() const
{
	return command;
}

bool isChessAlpha(wchar_t c)
{
	return (c >= L'A' && c <= L'H') || (c >= L'a' && c <= L'h');
}

bool isChessNumber(wchar_t c)
{
	return (c >= L'1' && c <= L'8');
}

bool Commands::isValidCommand() const
{
	if (command.length() == 5)
	{
		wchar_t firstChar = command[0];
		wchar_t secondChar = command[1];
		wchar_t thirdChar = command[2];
		wchar_t fourthChar = command[3];
		wchar_t fifthChar = command[4];

		if (thirdChar != L' ')return false;

		if (!isChessAlpha(firstChar) || !isChessAlpha(fourthChar))return false;

		if (!isChessNumber(secondChar) || !isChessNumber(fifthChar))return false;

		if (firstChar == fourthChar && secondChar == fifthChar) return false;

		return true;
	}
	return false;
}

bool Commands::isValidMove(const Board& board) const
{
	wchar_t firstChar = command[0];
	wchar_t secondChar = command[1];
	wchar_t fourthChar = command[3];
	wchar_t fifthChar = command[4];

	int startX = towlower(firstChar) - L'a';
	int startY = secondChar - L'1';
	int endX = towlower(fourthChar) - L'a';
	int endY = fifthChar - L'1';
	if (moveCorrect(board, startX, startY, endX, endY) && !isCheck(board)
		&& isFiguirSelected(board, startX, startY) && placeClear(board, endX, endY)) {
		return true;
	}
	return false;
}

void Commands::executeCommand(Board& board)
{
	wchar_t firstChar = command[0];
	wchar_t secondChar = command[1];
	wchar_t fourthChar = command[3];
	wchar_t fifthChar = command[4];

	int x1 = towlower(firstChar) - L'a';
	int y1 = secondChar - L'1';
	int x2 = towlower(fourthChar) - L'a';
	int y2 = fifthChar - L'1';

	board.movePiece(x1, y1, x2, y2);
}

void Commands::printHelp()
{
	std::wcout << L"Usage: <file>\n";
}

void Commands::printAvailableCommands()
{
	// Implement as needed
}

void Commands::printCurrentCommand()
{
	std::wcout << L"Current command: " << command << std::endl;
}

void Commands::clearCommand()
{
	command.clear();
}

bool Commands::placeClear(const Board& board, int x, int y) const
{
	if (board.getBoard(x, y) == L" ") {
		return true;
	}
	return false;
}

bool Commands::moveCorrect(const Board& board, int startX, int startY, int endX, int endY) const
{
	Piece* figure = board.getPiece(startX, startY);
	if (figure->checkValidMove(board, startX, startY, endX, endY)) {
		return true;
	}
	return false;
}

bool Commands::isCheck(const Board& board) const
{
	return false;
}

bool Commands::isFiguirSelected(const Board& board, int x, int y) const
{
	if (board.getBoard(x, y) != L" ") {
		return true;
	}
	return false;
}
