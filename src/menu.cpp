#include "raylib.h"
#include <iostream>

bool menu_start()
{
    bool some = false;
    while (!some && !(IsKeyPressed(KEY_ENTER)))
    {
        some = WindowShouldClose();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Bienvenue sur notre version de", 400, 200, 50, BLUE);
        DrawText("Bloons Tower Defense", 500, 250, 50, BLUE);
        DrawText("By Maëva, Aurélien and Alice", 650, 320, 20, DARKGRAY);
        DrawText("Press ENTER to start the game", 400, 500, 50, BLACK);
        EndDrawing();
    }
    return some;
}

void menu_victoire()
{
    while (!WindowShouldClose() && !(IsKeyPressed(KEY_ENTER)))
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("BRAVO tu as gagné !", 400, 200, 50, BLUE);
        DrawText("Bloons Tower Defense  ", 500, 250, 50, BLUE);
        DrawText("By Maëva, Aurélien and Alice", 650, 320, 20, DARKGRAY);
        DrawText("Press ENTER to start the game", 400, 500, 50, BLACK);
        EndDrawing();
    }
}

void menu_defaite()
{
    while (!WindowShouldClose() && !(IsKeyPressed(KEY_ENTER)))
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Bienvenue sur notre version de", 400, 200, 50, BLUE);
        DrawText("Bloons Tower Defense", 500, 250, 50, BLUE);
        DrawText("By Maëva, Aurélien and Alice", 650, 320, 20, DARKGRAY);
        DrawText("Press ENTER to start the game", 400, 500, 50, BLACK);
        EndDrawing();
    }
}