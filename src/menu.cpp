#include "raylib.h"
#include <iostream>

void menu() {
     while (!WindowShouldClose() && !(IsKeyPressed(KEY_ENTER)) ) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Bienvenue sur notre version de", 400, 200, 50, BLUE);
        DrawText("Bloons Tower Defense", 500, 250, 50, BLUE);
        DrawText("By Maeva, Aurélien and Alice", 650, 300, 20, DARKGRAY);
        DrawText("Press ENTER to start the game", 400, 500, 50, BLACK);
        EndDrawing();
    }
}


int main2(void){

    InitWindow(1600, 900, "Menu start");
    SetTargetFPS(60);

    menu();

    CloseWindow(); // Close window and OpenGL context
    return 0;
}

