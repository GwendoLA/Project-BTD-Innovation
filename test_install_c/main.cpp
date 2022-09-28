
#include "raylib.h"

#include <sqlite3.h>
#include <iostream>


static int screenWidth = 800;
static int screenHeight = 450;

int main(void) {
  std::cout << sqlite3_libversion() << '\n';
  
  InitWindow(screenWidth, screenHeight, "classic game: missile commander");
  CloseWindow();        // Close window and OpenGL context
  std::cout << sqlite3_libversion() << '\n';
  return 0;
}