
#include "raylib.h"
#include <iostream>

static int screenWidth = 800;
static int screenHeight = 450;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    std::cout << "Hello World!";
    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "classic game: missile commander");

    // InitGame();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    int index = 0;
    // Main game loop
    while (!WindowShouldClose() && index <= 100000) // Detect window close button or ESC key
    {
        index++;
        std::cout << '\r' << index;
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
        // Update and Draw
        //----------------------------------------------------------------------------------
        // UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }
#endif
    // De-Initialization
    //--------------------------------------------------------------------------------------
    // UnloadGame();         // Unload loaded data (textures, sounds, models...)

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    std::cout << "Goodbye World!";
    return 0;
}