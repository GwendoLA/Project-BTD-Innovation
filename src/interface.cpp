#include "raylib.h"
#include <iostream>
#include <stdlib.h>
#include "constantes.h"

int compteur_chemin = 0;
 // pour créer le chemin, constituer de rectangle disposé à l'aide d'une grille
void lignes_chemin(int x_depart, int y, int x_arrivee, Rectangle liste[36], bool inversion)
{
    if (inversion == false)
    {
        for (int i = 0; i < x_arrivee - x_depart + 1; i++)
        {
            Rectangle carre;
            carre.x = (x_depart + i - 1) * SQUARE_SIZE;
            carre.y = (y - 1) * SQUARE_SIZE;
            carre.width = SQUARE_SIZE;
            carre.height = SQUARE_SIZE;
            liste[compteur_chemin] = carre;
            compteur_chemin++;
        }
    }

    else
    {
        for (int i = 0; i < x_arrivee - x_depart + 1; i++)
        {
            Rectangle carre;
            carre.x = (x_arrivee - i - 1) * SQUARE_SIZE;
            carre.y = (y - 1) * SQUARE_SIZE;
            carre.width = SQUARE_SIZE;
            carre.height = SQUARE_SIZE;
            liste[compteur_chemin] = carre;
            compteur_chemin++;
        }
    }
}

void colonnes_chemin(int x, int y_depart, int y_arrivee, Rectangle liste[36], bool inversion)
{
    if (inversion == false)
    {
        for (int i = 0; i < y_arrivee - y_depart + 1; i++)
        {
            Rectangle carre;
            carre.x = (x - 1) * SQUARE_SIZE;
            carre.y = (y_depart - 1 + i) * SQUARE_SIZE;
            carre.width = SQUARE_SIZE;
            carre.height = SQUARE_SIZE;
            liste[compteur_chemin] = carre;
            compteur_chemin++;
        }
    }
    else
    {
        for (int i = 0; i < y_arrivee - y_depart + 1; i++)
        {
            Rectangle carre;
            carre.x = (x - 1) * SQUARE_SIZE;
            carre.y = (y_arrivee - 1 - i) * SQUARE_SIZE;
            carre.width = SQUARE_SIZE;
            carre.height = SQUARE_SIZE;
            liste[compteur_chemin] = carre;
            compteur_chemin++;
        }
    }
}
void creation_chemin(Rectangle chemin[36])
{
    lignes_chemin(1, 4, 2, chemin, false);
    colonnes_chemin(3, 2, 4, chemin, true);
    lignes_chemin(4, 2, 5, chemin, false);
    colonnes_chemin(5, 3, 6, chemin, false);
    lignes_chemin(3, 6, 4, chemin, true);
    colonnes_chemin(3, 7, 8, chemin, false);
    lignes_chemin(4, 8, 12, chemin, false);
    colonnes_chemin(12, 5, 7, chemin, true);
    lignes_chemin(9, 5, 11, chemin, true);
    colonnes_chemin(9, 2, 4, chemin, true);
    lignes_chemin(10, 2, 11, chemin, false);
    colonnes_chemin(11, 1, 1, chemin, true);
}

void draw_lignes()
{
    for (int i = 0; i < screenWidth / SQUARE_SIZE + 1; i++)
    {
        DrawLineV({(float)(SQUARE_SIZE * i), 0.0}, {(float)(SQUARE_SIZE * i), (float)(screenHeight)}, LIGHTGRAY);
    }

    for (int i = 0; i < screenHeight / SQUARE_SIZE + 1; i++)
    {
        DrawLineV({0.0, (float)(SQUARE_SIZE * i)}, {(float)(screenWidth), (float)(SQUARE_SIZE * i)}, LIGHTGRAY);
    }
}