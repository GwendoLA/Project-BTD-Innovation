
#include "raylib.h"
#include <iostream>

static int screenWidth = 1600;
static int screenHeight = 900;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    std::cout << "Hello World!";
    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
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
        DrawText(TextFormat("ROUND %4i \nMONEY %4i \nVIES %4i", index, -2*index, -index), 1250, 10, 40, MAGENTA);
        EndDrawing();
        // Update and Draw
        //----------------------------------------------------------------------------------
        // UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // UnloadGame();         // Unload loaded data (textures, sounds, models...)

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    std::cout << "Goodbye World!";
    return 0;
}