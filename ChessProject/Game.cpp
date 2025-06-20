﻿#include "Game.h"
#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "Commands.h"
#include "Board.h"
#include <fstream> 
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"


int Game::counter = 0;
GameType Game::type = GameType::NORMAL;
LastMove Game::lastMove(0, 0, 0, 0, nullptr);
Color Game::currentPlayer = Color::WHITE;

int whiteTime = 600;
int blackTime = 600;

void Game::moveCursorTo(short x, short y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };
	SetConsoleCursorPosition(hConsole, position);
}

void printTimer(const wchar_t* player, int seconds, int x, int y) {
	if (GameType::NO_TIME == Game::type) {
		return;
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Game::moveCursorTo(x, y);
	int mins = seconds / 60;
	int secs = seconds % 60;
	std::wcout << player << L" Time: " << mins << L":" << (secs < 10 ? L"0" : L"") << secs << L"  ";
}

void introduction() {
	std::wcout << L"Welcome to the Chess Game!" << std::endl;
	std::wcout << L"Choose game type:\n"
		<< L"1. Normal\n"
		<< L"2. Blitz\n"
		<< L"3. No Time\n"
		<< L"4. Add Time\n"
		<< L"Enter your choice (1-4): ";

}

void Game::setGameState(GameType gameType)
{
	type = gameType;
}

void Game::GameState(int choice) {
	switch (choice) {
	case 1:
		std::wcout << L"Game type: Normal" << std::endl;
		setGameState(GameType::NORMAL);
		break;
	case 2:
		std::wcout << L"Game type: Blitz" << std::endl;
		setGameState(GameType::BLITZ);
		break;
	case 3:
		std::wcout << L"Game type: No Time" << std::endl;
		setGameState(GameType::NO_TIME);
		break;
	case 4:
		std::wcout << L"Game type: Add Time" << std::endl;
		setGameState(GameType::ADDTIME);
		break;
	default:
		std::wcout << L"Unknown game type! Setting to NORMAL." << std::endl;
		setGameState(GameType::NORMAL);
		break;
	}
}

GameType Game::getType() const
{
	return type;
}

void Game::setTime()
{
	switch (type) {
	case GameType::NORMAL:
		whiteTime = 600; // 10 minutes
		blackTime = 600; // 10 minutes
		break;
	case GameType::BLITZ:
		whiteTime = 300; // 5 minutes
		blackTime = 300; // 5 minutes
		break;
	case GameType::NO_TIME:
		whiteTime = -1; // No time limit
		blackTime = -1; // No time limit
		break;
	case GameType::ADDTIME:
		whiteTime = 180; // 3 minutes
		blackTime = 180; // 3 minutes
		break;
	default:
		std::wcout << L"Unknown game type! Setting to NORMAL." << std::endl;
		setGameState(GameType::NORMAL);
		break;
	}

}

bool Game::isSquareUnderAttack(const Board& board, int x, int y, Color color) {
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			Piece* p = board.getPiece(col, row);
			if (p != nullptr && p->getColor() != color) {
				if (p->checkValidMove(board, col, row, x, y)) {
					return true;
				}
			}
		}
	}
	return false;
}

void Game::start()
{
	introduction();
	int choice = 0;
	std::wcin >> choice;
	while (choice && choice < 1 && choice > 4) {
		std::wcin >> choice;
		break;
	}

	GameState(choice);
	cleanConsole();
	Sleep(3000);
	setupConsole();
	printChessBoard();
}

void Game::end(Color curPlayer)
{
	cleanConsole();
	std::wcout << "\nGame Over!\n";
	std::wcout << (curPlayer == Color::WHITE ? L"White" : L"Black") << L" wins!\n";
	Sleep(2000);
	exit(0);
}

void Game::save(Board board)
{
	// Save game state to a file 
	saveGameInFile(board);
	std::wcout << L"Game saved!" << std::endl;
}

void Game::load(Board& board)
{
	// Load game state from a file 
	loadGameFromFile(board);
	std::wcout << L"Game loaded!" << std::endl;
}

void Game::printChessBoard()
{

	Board board;
	board.initializeBoard();
	board.printBoard();
	std::wcout << L"\n";
	board.printReverseBoard();
	gameLoop(board);
}

// Set color for Windows CMD
void Game::setColor(int textColor, int bgColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, textColor + (bgColor << 4));
}

void Game::cleanConsole()
{
	system("cls");
}

void Game::setupConsole()
{
	changeConsoleFont();
}
void Game::changeConsoleFont() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
	cfi.dwFontSize.X = 20; // Font size
	cfi.dwFontSize.Y = 46; // Font size
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"MS Gothic"); // Font name
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void Game::clearConsoleRow(int row)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE) return;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
	int consoleWidth = csbi.dwSize.X;
	COORD coord = { 0, static_cast<SHORT>(row) };
	DWORD charsWritten;
	FillConsoleOutputCharacterW(hConsole, L' ', consoleWidth, coord, &charsWritten);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleWidth, coord, &charsWritten);
	SetConsoleCursorPosition(hConsole, coord);
}

void cleanInput()
{
	Game::clearConsoleRow(20);
	//clearConsoleRow(19);
}

void Game::gameLoop(Board& board)
{
	setTime();
	DWORD turnStart = GetTickCount64();
	printTimer(L"White", whiteTime, 20, 3);
	printTimer(L"Black", blackTime, 20, 14);
	counter = 0;
	moveCursorTo(0, 20);
	std::wcout << L"White's move: ";
	while (true) {
		if (whiteTime <= 0 && type != GameType::NO_TIME) {
			cleanConsole();
			std::wcout << L"\nBlack wins by timeout!\n";
			Sleep(2000);
			end(Color::BLACK);
		}
		if (blackTime <= 0 && type != GameType::NO_TIME) {
			cleanConsole();
			std::wcout << L"\nWhite wins by timeout!\n";
			Sleep(2000);
			end(Color::WHITE);
		}
		Commands commands;
		bool moveSucceeded = false;
		try {
			commands.processCommands(board);
			moveSucceeded = true;
			if (commands.isMate(board)) {
				Sleep(2000);
				end(currentPlayer);
			}
		}
		catch (const std::exception& e) {
			Sleep(500);
		}
		cleanInput();
		DWORD turnEnd = GetTickCount64();
		int elapsedSeconds = (turnEnd - turnStart) / 1000;
		if (counter % 2 == 0)
			whiteTime -= elapsedSeconds;
		else
			blackTime -= elapsedSeconds;
		printTimer(L"White", whiteTime, 20, 3);
		printTimer(L"Black", blackTime, 20, 14);

		if (moveSucceeded) {
			counter++;
		}
		turnStart = GetTickCount64();

		moveCursorTo(0, 20);
		if (counter % 2 == 0) {
			std::wcout << L"White's move: ";
			currentPlayer = Color::WHITE;
		}
		else {
			std::wcout << L"Black's move: ";
			currentPlayer = Color::BLACK;
		}
	}

}


void Game::saveGameInFile(const Board board)
{
	const char EMPTY_SYMBOL = '0 ';

	std::wofstream file("Saves.txt", std::ios::out);
	file.imbue(std::locale("en_US.UTF-8"));

	if (!file.is_open()) {
		std::wcerr << L"❌ Failed to open Saves.txt for writing.\n";
		return;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece* piece = board.getPiece(j, i);
			if (piece != nullptr) {
				file << piece->getSymbol();
				if (piece->getSymbol() == L"♟")
					file << L" ";
			}
			else
			{
				file << '0' << L" ";
			}
		}
		file << L"\n";
	}
	file << (Game::currentPlayer == Color::WHITE ? '1' : '2') << L" ";
	file << lastMove.startX << L" " << lastMove.startY << L" "
		<< lastMove.endX << L" " << lastMove.endY << L" "
		<< (lastMove.movedPiece ? lastMove.movedPiece->getSymbol() : nullptr) << L"\n";
	file.close();
	std::wcout << L"✅ Game board saved successfully to Saves.txt\n";
	clearConsoleRow(20);
}

void Game::loadGameFromFile(Board& board)
{
	//const char EMPTY_SYMBOL = '0 ';
	std::wifstream file("Saves.txt", std::ios::in);
	file.imbue(std::locale("en_US.UTF-8"));

	if (!file.is_open()) {
		std::wcerr << L"❌ Failed to open Saves.txt for reading.\n";
		return;
	}

	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			std::wstring symbol;
			file >> symbol;
			board.setBoard(col, row, nullptr);

			if (symbol == L"0") {
				continue;
			}

			Color color = iswupper(symbol[0]) || symbol == L"♔" || symbol == L"♕" || symbol == L"♖" || symbol == L"♗" || symbol == L"♘" || symbol == L"♙"
				? Color::WHITE
				: Color::BLACK;

			Piece* piece = nullptr;

			if (symbol == L"♖" || symbol == L"♜")
				piece = new Rook({ col, row }, color);
			else if (symbol == L"♘" || symbol == L"♞")
				piece = new Knight({ col, row }, color);
			else if (symbol == L"♗" || symbol == L"♝")
				piece = new Bishop({ col, row }, color);
			else if (symbol == L"♕" || symbol == L"♛")
				piece = new Queen({ col, row }, color);
			else if (symbol == L"♔" || symbol == L"♚")
				piece = new King({ col, row }, color);
			else if (symbol == L"♙" || symbol == L"♟")
				piece = new Pawn({ col, row }, color);


			if (piece)
				board.setBoard(col, row, piece);
		}
	}
	//clear spaces
	file >> std::ws;
	//get clean
	wchar_t player = file.get();

	Game::currentPlayer = (player == '1') ? Color::WHITE : Color::BLACK;
	counter = (Game::currentPlayer == Color::WHITE) ? 0 : 1;
	std::wstring movedPiece;
	int startX, startY, endX, endY;
	file >> startX >> startY >> endX >> endY;
	file >> movedPiece;
	Piece* piece = nullptr;
	if (movedPiece == L"0") {
		piece = nullptr; 
	}
	else {
		Color color = iswupper(movedPiece[0]) ? Color::WHITE : Color::BLACK;
		if (movedPiece == L"♖" || movedPiece == L"♜")
			piece = new Rook({ endX, endY }, color);
		else if (movedPiece == L"♘" || movedPiece == L"♞")
			piece = new Knight({ endX, endY }, color);
		else if (movedPiece == L"♗" || movedPiece == L"♝")
			piece = new Bishop({ endX, endY }, color);
		else if (movedPiece == L"♕" || movedPiece == L"♛")
			piece = new Queen({ endX, endY }, color);
		else if (movedPiece == L"♔" || movedPiece == L"♚")
			piece = new King({ endX, endY }, color);
		else if (movedPiece == L"♙" || movedPiece == L"♟")
			piece = new Pawn({ endX, endY }, color);
	}
	lastMove = LastMove(startX, startY, endX, endY, piece);
	file.close();
	std::wcout << L"✅ Game loaded successfully from Saves.txt\n";
}




