#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "Game.h"

template <typename T>
void sumNumbers(T a, T b) {
	std::cout << "Sum: " << (a + b) << std::endl;
}

template <typename T>
void smth(T a, T c) {
	std::cout << "Sum: " << (a + c) << std::endl;
}

int main() {
   Game game;
   game.start();
   return 0;
}
