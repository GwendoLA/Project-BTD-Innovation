#include "raylib.h"
#include <iostream>
#include <stdlib.h> 
#include "constantes.h"


int compteur_chemin = 0;


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