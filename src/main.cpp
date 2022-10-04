
#include "raylib.h"
#include <iostream>
#define SQUARE_SIZE 100
static int screenWidth = 1600;
static int screenHeight = 900;
static Vector2 offset = {0};

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{

    // Initialisation fenetre
    InitWindow(screenWidth, screenHeight, "classic game: missile commander");

    SetTargetFPS(60);

    //--------------------------------------------------------------------------------------
    int index = 0;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        index++;
        std::cout << '\r' << index;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < screenWidth / SQUARE_SIZE + 1; i++)
        {
            DrawLineV({SQUARE_SIZE * i + offset.x / 2, offset.y / 2}, {SQUARE_SIZE * i + offset.x / 2, screenHeight - offset.y / 2}, LIGHTGRAY);
        }

        for (int i = 0; i < screenHeight / SQUARE_SIZE + 1; i++)
        {
            DrawLineV({offset.x / 2, SQUARE_SIZE * i + offset.y / 2}, {screenWidth - offset.x / 2, SQUARE_SIZE * i + offset.y / 2}, LIGHTGRAY);
        }
        DrawText(TextFormat("ROUND %4i \nMONEY %4i \nVIES %4i", index, -2 * index, -index), 1250, 10, 40, MAGENTA);
        // DrawRectangle(0, 100, 300, 80, DARKGRAY);  // gauche, haut, longueur, largeur
        
        for (int i=1; i<6; i++)
        {
             DrawRectangle(0, SQUARE_SIZE, i*SQUARE_SIZE, SQUARE_SIZE, DARKGRAY);
        }
        
        // DrawRectangle(300, 400, 300, 80, DARKGRAY);
        // DrawRectangle(600, 180, 80, 300, DARKGRAY);
        // DrawRectangle(600, 100, 500, 80, DARKGRAY);
        // DrawRectangle(1100, 100, 80, 550, DARKGRAY);

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    std::cout << "Goodbye World!";
    return 0;
}