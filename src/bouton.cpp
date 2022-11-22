#include "raylib.h"
#include <iostream>
#include <stdlib.h> 
#include "constantes.h"

typedef struct Button
{
    bool etat; //cliqué ou non 
    Vector2 position;
    Vector2 taille;
    Color color;
    char ecriture[30]; // taille de l'écriture
} Button;

Button creer_bouton(Vector2 position, Vector2 taille, char ecriture[30])
{
    Button bouton;
    bouton.etat = false;
    bouton.position = position;
    bouton.taille = taille;
    bouton.color = GRAY;
    strcpy(bouton.ecriture, ecriture);
    return bouton;
}

bool detect_click(Button bouton)
{
    Rectangle rectangle{bouton.position.x, bouton.position.y, bouton.taille.x, bouton.taille.y};
    Vector2 position_souris = GetMousePosition();

    if (CheckCollisionPointRec(position_souris, rectangle))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            return true;
    }

    return false;
}

void dessiner_bouton(Button bouton, int taille_ecriture)
{
    DrawRectangleV(bouton.position, bouton.taille, GRAY);
    DrawText(TextFormat(bouton.ecriture), bouton.position.x + 0.25 * SQUARE_SIZE, bouton.position.y + 0.25 * SQUARE_SIZE, taille_ecriture, WHITE);
}


