#include "Game.h"
#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "Commands.h"
#include "Board.h"

static int counter = 0;

void Game::start()
{
	std::wcout << L"Welcome to the Chess Game!" << std::endl;
	cleanConsole();
	Sleep(3000);
	setupConsole();
	printChessBoard();
}

void Game::end()
{
	save();
	exit(0);
}

void Game::save()
{
	// Save game state to a file 
	saveGameInFile();
	std::wcout << L"Game saved!" << std::endl;
}

void Game::load()
{
	// Load game state from a file 
	loadGameFromFile();
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
	cfi.dwFontSize.X = 32; // Font size
	cfi.dwFontSize.Y = 70; // Font size
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"MS Gothic"); // Font name
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void clearConsoleRow(int row)
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
	clearConsoleRow(20);
	clearConsoleRow(19);

}

void Game::gameLoop(Board& board)  
{  
   counter = 0;  
   std::wcout << L"White's move: ";  
   while (true) {  
       Commands commands;  
       try {  
           commands.processCommands(board);  
           counter++;  
       }  
       catch (const std::exception& e) {  
           Sleep(1000);  
       }  
       cleanInput();  
       if (counter % 2 == 0) {  
           std::wcout << L"White's move: ";      
       }  
       else if(counter % 2 != 0){  
           std::wcout << L"Black's move: ";  
       }  
   }  
}

void Game::saveGameInFile()
{
	

}

void Game::loadGameFromFile()
{


}



