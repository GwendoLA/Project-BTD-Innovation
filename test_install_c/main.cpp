
#include "raylib.h"
#include <iostream>

static int screenWidth = 800;
static int screenHeight = 450;

int main(void) {
    std::cout << "Hello World!";
    InitWindow(screenWidth, screenHeight, "classic game: missile commander");
    CloseWindow();        // Close window and OpenGL context
    return 0;
}