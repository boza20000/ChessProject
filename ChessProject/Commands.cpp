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
	if (isValidCommand(board) && isValidMove(board)
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
	Game::loadGameFromFile(board);
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

void Commands::executeCommand(Board& board, bool isSimulation)
{
	wchar_t firstChar = command[0];
	wchar_t secondChar = command[1];
	wchar_t fourthChar = command[3];
	wchar_t fifthChar = command[4];

	int startCol = towlower(firstChar) - L'a';
	int startRow = 8 - (secondChar - L'0');
	int endCol = towlower(fourthChar) - L'a';
	int endRow = 8 - (fifthChar - L'0');
	board.movePiece(startCol, startRow, endCol, endRow, isSimulation);
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
	// temp board is shallow copy for some reason fix
	Board tempBoard = board;
	executeCommand(tempBoard, true);
	if (isCheck(tempBoard, Game::currentPlayer)) {
		return true;
	}
	return false;
}

Position Commands::findKing(const Board& board, Color defender)const {
	Position kingPos = { -1, -1 };
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			Piece* p = board.getPiece(x, y);
			if (p && (board.getBoard(x, y) == L"♚ " || board.getBoard(x, y) == L"♔ ") && p->getColor() == defender) {
				kingPos = { x, y };
				break;
			}
		}
	}
	return kingPos;
}

bool Commands::isPieceProtected(const Board& board, Piece* targetPiece)const {
	if (!targetPiece) return false;

	int targetX = targetPiece->getPosition().x;
	int targetY = targetPiece->getPosition().y;
	Color targetColor = targetPiece->getColor();

	for (int x = 0; x < 8; ++x) {
		for (int y = 0; y < 8; ++y) {
			Piece* potentialProtector = board.getPiece(x, y);
			if (potentialProtector && potentialProtector != targetPiece &&
				potentialProtector->getColor() == targetColor) {

				if (potentialProtector->checkValidMove(board, x, y, targetX, targetY)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool isKing(Piece* piece) {
	if (piece->getSymbol() == L"♚ " || piece->getSymbol() == L"♔ ") {
		return true;
	}
	return false;
}
bool Commands::isPathClear(const Board&board,Color defender,Position * interceptPath,int pathLen)const {
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			Piece* defenderPiece = board.getPiece(x, y);
			if (!defenderPiece || defenderPiece->getColor() != defender)
				continue;

			for (int i = 0; i < pathLen; ++i) {
				Position target = interceptPath[i];
				if (defenderPiece->checkValidMove(board, x, y, target.x, target.y)) {
					Piece* targetPiece = board.getPiece(target.x, target.y);

					// Skip invalid king captures of protected attackers
					if (isKing(defenderPiece) && targetPiece &&
						targetPiece->getColor() != defender &&
						isPieceProtected(board, targetPiece)) {
						continue;
					}

					// Simulate move
					Board tempBoard = board;
					tempBoard.makeMove(x, y, target.x, target.y, true);
					if (!isCheck(tempBoard, defender)) {
						return false; 
					}
				}
			}
		}
	}
	return true;
}

bool Commands::isEscapable(const Board& board, const Position& kingPos,Color defender) const
{
	for (int dx = -1; dx <= 1; ++dx) {
		for (int dy = -1; dy <= 1; ++dy) {
			if (dx == 0 && dy == 0) continue;

			int newX = kingPos.x + dx;
			int newY = kingPos.y + dy;

			if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
				Piece* king = board.getPiece(kingPos.x, kingPos.y);
				if (king && king->checkValidMove(board, kingPos.x, kingPos.y, newX, newY)) {
					Board tempBoard = board;
					tempBoard.makeMove(kingPos.x, kingPos.y, newX, newY, true); // simulate move
					if (!isCheck(tempBoard, defender)) {
						return true; // king can escape
					}
				}
			}
		}
	}
	return false;
}

bool Commands::isMate(const Board& board) const {
	Color attacker = Game::currentPlayer;
	Color defender = (attacker == Color::WHITE) ? Color::BLACK : Color::WHITE;
	Position kingPos = findKing(board, defender);
	if (!isCheck(board, defender)) {
		return false;
	}
	const LastMove& lastMove = Game::lastMove;
	Piece* attackerPiece = lastMove.movedPiece;
	Position attackerPos{ lastMove.endX, lastMove.endY };
	if (!attackerPiece || attackerPiece->getColor() != attacker) {
		return true;
	}
	Position interceptPath[8];
	int pathLen = 0;
	interceptPath[pathLen++] = attackerPos;
	std::wstring attackerSymbol = board.getBoard(attackerPos.x, attackerPos.y);
	if (attackerSymbol != L"♞ " && attackerSymbol != L"♘ ") {
		int dx = (kingPos.x == attackerPos.x) ? 0 : (kingPos.x > attackerPos.x ? 1 : -1);
		int dy = (kingPos.y == attackerPos.y) ? 0 : (kingPos.y > attackerPos.y ? 1 : -1);

		Position cur = { attackerPos.x + dx, attackerPos.y + dy };
		while (!(cur.x == kingPos.x && cur.y == kingPos.y) && pathLen < 8) {
			interceptPath[pathLen++] = cur;
			cur.x += dx;
			cur.y += dy;
		}
	}
	if (pathLen > 0 && !isPathClear(board, defender, interceptPath, pathLen)) {
		return false; 
	}
	if (isEscapable(board, kingPos, defender)) {
		return false; 
	}	
	return true;
}


