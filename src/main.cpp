
#include "raylib.h"
#include <iostream>
#include "menu.cpp"
#include <string.h>


#define SQUARE_SIZE 100

static int screenWidth = 1600;
static int screenHeight = 900;
int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
bool btnAction = false;         // Button action should be activated

typedef struct Button {
    bool etat;
    Vector2 position;
    Vector2 taille;
    Color color; 
    char ecriture [30];
} Button;

Button creer_bouton (Vector2 position, Vector2 taille, char ecriture [30]) {
    Button bouton;
    bouton.etat= false;
    bouton.position= position;
    bouton.taille= taille;
    bouton.color= GRAY;
    strcpy(bouton.ecriture, ecriture);
    return bouton;
}

bool detect_click (Button bouton) {
    Rectangle rectangle {bouton.position.x , bouton.position.y , bouton.taille.x , bouton.taille.y};
    Vector2 position_souris = GetMousePosition();

    if (CheckCollisionPointRec(position_souris, rectangle)) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) return true;
    }

    return false; 
}

void dessiner_bouton (Button bouton) {
    DrawRectangle(bouton.position.x , bouton.position.y , bouton.taille.x , bouton.taille.y, MAGENTA);
    DrawText(TextFormat(bouton.ecriture), bouton.position.x, bouton.position.y, 40, GREEN);
}

void lignes_chemin(int x_depart, int y, int x_arrivee)
{
    for (int i = 0; i < x_arrivee - x_depart + 1; i++)
    {
        DrawRectangle((x_depart + i - 1) * SQUARE_SIZE, (y - 1) * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, DARKGRAY);
    }
}

void colonnes_chemin(int x, int y_depart, int y_arrivee)
{
    for (int i = 0; i < y_arrivee - y_depart + 1; i++)
    {
        DrawRectangle((x - 1) * SQUARE_SIZE, (y_depart - 1 + i) * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, DARKGRAY);
    }
}



int main(void)
{
    // Initialisation fenetre
    InitWindow(screenWidth, screenHeight, "classic game: missile commander");

    SetTargetFPS(60);

    menu();
    //--------------------------------------------------------------------------------------
    int index = 0;

    Button bouton1= creer_bouton ({13*SQUARE_SIZE, 7*SQUARE_SIZE}, {2*SQUARE_SIZE, SQUARE_SIZE}, "COUCOU");

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        //dessiner_bouton(bouton1);
        index++;
        std::cout << '\r' << index;

        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        dessiner_bouton(bouton1);

        for (int i = 0; i < screenWidth / SQUARE_SIZE + 1; i++)
        {
            DrawLineV({(float)(SQUARE_SIZE * i), 0.0}, {(float)(SQUARE_SIZE * i), (float)(screenHeight)}, LIGHTGRAY);
        }

        for (int i = 0; i < screenHeight / SQUARE_SIZE + 1; i++)
        {
            DrawLineV({0.0, (float)(SQUARE_SIZE * i)}, {(float)(screenWidth), (float)(SQUARE_SIZE * i)}, LIGHTGRAY);
        }

        DrawText(TextFormat(" ROUND %4i \nMONEY %4i \nVIES %4i", index, -2 * index, -index), 1250, 10, 40, MAGENTA);
        // DrawRectangle(0, 100, 300, 80, DARKGRAY);  // gauche, haut, longueur, largeur

        lignes_chemin(1, 4, 2);
        colonnes_chemin(3, 2, 4);
        lignes_chemin(4, 2, 5);
        colonnes_chemin(5, 3, 6);
        lignes_chemin(3, 6, 4);
        colonnes_chemin(3, 7, 8);
        lignes_chemin(4, 8, 12);
        colonnes_chemin(12, 5, 7);
        lignes_chemin(9, 5, 11);
        colonnes_chemin(9, 2, 4);
        lignes_chemin(10, 2, 11);
        colonnes_chemin(11, 1, 1);

        // Verif si le bouton est cliqué
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (detect_click (bouton1)) {
                std::cout << "coucou";
            }
        }


        // DrawRectangle(300, 400, 300, 80, DARKGRAY);
        // DrawRectangle(600, 180, 80, 300, DARKGRAY);
        // DrawRectangle(600, 100, 500, 80, DARKGRAY);
        // DrawRectangle(1100, 100, 80, 550, DARKGRAY);

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    
    
    std::cout << " Goodbye World!";
    return 0;
}
