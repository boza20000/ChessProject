// Commands.cpp
#include "Commands.h"
#include <iostream>
#include "Board.h"
#include "Game.h"
#include "King.h"

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
	if (isValidCommand(board) && isValidMove(board) && !isCheck(board,Game::currentPlayer)
		&& isRightColorFigure(board) && !revailsCheck(board)) {
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

bool Commands::isValidCommand(Board& board) const
{
	if (command == L"-save" || command == L"-s" || command == L"save")
	{
		save(board);
		return true;
	}
	else if (command == L"-load" || command == L"-l" || command == L"load")
	{
		load(board);
		return true;
	}
	if (command.length() == 5)
	{
		wchar_t firstChar = command[0];
		wchar_t secondChar = command[1];
		wchar_t thirdChar = command[2];
		wchar_t fourthChar = command[3];
		wchar_t fifthChar = command[4];

		if (thirdChar != L' ') return false;

		if (!isChessAlpha(firstChar) || !isChessAlpha(fourthChar)) return false;

		if (!isChessNumber(secondChar) || !isChessNumber(fifthChar)) return false;

		if (firstChar == fourthChar && secondChar == fifthChar) return false;

		return true;
	}
	return false;
}

void Commands::save(Board& board)
{
	Game::saveGameInFile(board);
}

void Commands::load(Board& board)
{
	Game::loadGameFromFile();
	std::wcout << L"Game loaded!" << std::endl;
	board.repaint();
}

bool Commands::isValidMove(const Board& board) const
{
	if (command.length() < 5) return false;

	wchar_t firstChar = command[0];
	wchar_t secondChar = command[1];
	wchar_t fourthChar = command[3];
	wchar_t fifthChar = command[4];

	int startX = towlower(firstChar) - L'a';
	int startY = 8 - (secondChar - L'0');  // corrected y-coordinate
	int endX = towlower(fourthChar) - L'a';
	int endY = 8 - (fifthChar - L'0');    // corrected y-coordinate

	if (moveCorrect(board, startX, startY, endX, endY)
		&& isFiguirSelected(board, startX, startY)) {
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

	int startCol = towlower(firstChar) - L'a';
	int startRow = 8 - (secondChar - L'0');
	int endCol = towlower(fourthChar) - L'a';
	int endRow = 8 - (fifthChar - L'0');
	board.movePiece(startCol, startRow, endCol, endRow);
}

void Commands::printHelp()
{
	std::wcout << L"Usage: <file>\n";
}

void Commands::printAvailableCommands()
{
	// Implement when needed
}

void Commands::printCurrentCommand()
{
	std::wcout << L"Current command: " << command << std::endl;
}

void Commands::clearCommand()
{
	command.clear();
}

bool Commands::isRightColorFigure(const Board& board) const
{
	int startX = towlower(command[0]) - L'a';
	int startY = 8 - (command[1] - L'0');
	Piece* figure = board.getPiece(startX, startY);
	if (figure->getColor() != Game::currentPlayer) {	
		return false;
	}
	return true;
}

bool Commands::moveCorrect(const Board& board, int startX, int startY, int endX, int endY) const
{
	if (Piece* figure = board.getPiece(startX, startY)) {
		return figure->checkValidMove(board, startX, startY, endX, endY);
	}

	return false;
}

bool Commands::isCheck(const Board& board, const Color playerColor) const {
	Color currentPlayer = playerColor;
	Color opponent = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;

	//Find the king
	Position kingPos;
	bool found = false;
	for (int y = 0; y < 8 && !found; ++y) {
		for (int x = 0; x < 8 && !found; ++x) {
			Piece* piece = board.getPiece(x, y);
			if (piece && (board.getBoard(x, y) == L"♚ " || board.getBoard(x, y) == L"♔ ") && piece->getColor() == currentPlayer) {
				kingPos = { x, y };
				found = true;
			}
		}
	}
	if (!found) return false;

	// Check if any enemy piece can attack the king
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			Piece* p = board.getPiece(x, y);
			if (p && p->getColor() == opponent) {
				if (p->checkValidMove(board, x, y, kingPos.x, kingPos.y)) {
					return true;  // King is in check
				}
			}
		}
	}

	return false;
}


bool Commands::isFiguirSelected(const Board& board, int x, int y) const
{
	return board.getBoard(x, y) != L" ";
}

bool Commands::revailsCheck(const Board& board)
{
	Board tempBoard = board;
	executeCommand(tempBoard);
	if (isCheck(tempBoard,Game::currentPlayer)) {
		return true;
	}
	return false;
}

bool Commands::isMate(const Board& board) const {
	Color currentPlayer = Game::currentPlayer;
	Color opponent = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
	//check if opposition king is in check
	if (!isCheck(board,opponent)) {
		return false; // If the king is not in check, it's not mate
	}
	// Loop through all pieces of the current player
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			Piece* piece = board.getPiece(x, y);
			if (!piece || piece->getColor() != opponent) continue;

			// Try all possible moves for this piece
			for (int newY = 0; newY < 8; ++newY) {
				for (int newX = 0; newX < 8; ++newX) {
					if (!piece->checkValidMove(board, x, y, newX, newY)) continue;

					// Simulate the move
					Board tempBoard = board;
					tempBoard.movePiece(x, y, newX, newY);

					// Check if still in check
					if (!isCheck(tempBoard,opponent)) {
						return false;
					}
				}
			}
		}
	}
	return true;
}
