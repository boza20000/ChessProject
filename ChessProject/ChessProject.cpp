#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "Game.h"

int main() {
   (void)_setmode(_fileno(stdout), _O_U16TEXT);
   Game game;
   game.start();
   return 0;
}
