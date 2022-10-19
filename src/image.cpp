#include "raylib.h"
#include <iostream>

int main(void)
{

    InitWindow(1600, 900, " Menu start");
    SetTargetFPS(60);
    Image tour = LoadImage("C:/Users/maeva/OneDrive/Images/courbe.png");
    Texture2D texture = LoadTextureFromImage(tour); 
    
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureV(texture, {20,20}, WHITE);
        
        EndDrawing();
    }
      UnloadTexture(texture);
      UnloadImage(tour);
      CloseWindow();
      return 0;

}
