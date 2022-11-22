#include "raylib.h"
#include <iostream>
#include "constantes.h"

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
        DrawText("Appuie sur ENTRER pour commencer à jouer", 300, 500, 50, BLACK);
        EndDrawing();
    }
    return some;
}

void menu_victoire()
{
    Image im_fleche = LoadImage(PATH_VICTOIRE);
    Texture2D texture_fleche = LoadTextureFromImage(im_fleche);
    while (!WindowShouldClose() && !(IsKeyPressed(KEY_ENTER)))
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // DrawTexture(texture_fleche, 600, 150, WHITE);
        DrawText("BRAVO tu as gagné !", 520, 200, 50, BLUE);
        DrawText("Merci d'avoir jouer à Monkey Tower Defense", 250, 250, 50, BLUE);
        DrawText("By Maëva, Aurélien and Alice", 650, 320, 20, DARKGRAY);
        DrawText("Appuie sur ENTRER pour quitter le jeu", 320, 500, 50, BLACK);
        EndDrawing();
    }
    UnloadImage(im_fleche);
    UnloadTexture(texture_fleche); // Unload texture from VRAM
}

void menu_defaite()
{
    Image im_fleche = LoadImage(PATH_DEFAITE);
    Texture2D texture_fleche = LoadTextureFromImage(im_fleche);
    while (!WindowShouldClose() && !(IsKeyPressed(KEY_ENTER)))
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // DrawTexture(texture_fleche, 600, 150, WHITE);
        DrawText("Dommage tu as perdu, retente ta chance.", 300, 200, 50, BLUE);
        DrawText("Merci d'avoir jouer à Monkey Tower Defense", 250, 250, 50, BLUE);
        DrawText("By Maëva, Aurélien and Alice", 650, 320, 20, DARKGRAY);
        DrawText("Appuie sur ENTRER pour quitter le jeu", 320, 500, 50, BLACK);
        EndDrawing();
    }
    UnloadImage(im_fleche);
    UnloadTexture(texture_fleche); // Unload texture from VRAM
}