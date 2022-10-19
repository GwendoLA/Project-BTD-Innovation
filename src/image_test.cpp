
#include "raylib.h"

#include <stdlib.h> // Required for: free()

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1800;
    const int screenHeight = 1450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - image processing");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    Image imOrigin = LoadImage("C:/Users/Aurel/OneDrive/Documents/GitHub/Project-BTD-Innovation/src/901811.png"); // Loaded in CPU memory (RAM)
    ImageFormat(&imOrigin, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);                                                    // Format image to RGBA 32bit (required for texture update) <-- ISSUE
    Texture2D texture = LoadTextureFromImage(imOrigin);                                                           // Image converted to texture, GPU memory (VRAM)

    SetTargetFPS(60);
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(texture, screenWidth - texture.width - 60, screenHeight / 2 - texture.height / 2, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture); // Unload texture from VRAM
    UnloadImage(imOrigin);  // Unload image-origin from RAM

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}