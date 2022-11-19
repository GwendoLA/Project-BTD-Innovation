
#include "raylib.h"
#include <iostream>
#include <vector>
#include "constantes.h"

typedef struct Singe
{
    bool etat;
    Vector2 position;
    Vector2 taille;
    int range; // zone de detection des ballons
    int ang;   // angle pris par le singe, utile pour les prochaines améliorations
    int fatigue;
    int fatigue_tir;
    Color color;
    Texture texture;

} Singe;

Singe creer_singe(Vector2 position, int fatigue_tir)
{
    Singe singe;
    singe.etat = false;
    singe.position = position;
    singe.taille = {80, 80};
    singe.range = 200; // choix du range par defaut
    singe.ang = 10;
    singe.fatigue = 0;
    singe.fatigue_tir = fatigue_tir;
    singe.color = RED;
    return singe;
}

void dessiner_singe(Singe singe, Texture text)
{
    DrawTexture(text, singe.position.x, singe.position.y, WHITE);
    // DrawRectangleRec({singe.position.x + 10, singe.position.y + 10, singe.taille.x, singe.taille.y}, RAYWHITE);
}

bool check_collision_singe(Singe singe, Rectangle rectangles[36])
{
    Rectangle s;
    s.x = singe.position.x + 10;
    s.y = singe.position.y + 10;
    s.height = singe.taille.x;
    s.width = singe.taille.y;
    for (int i = 0; i < 36; i++)
    {
        if (CheckCollisionRecs(s, rectangles[i]))
        {
            return true;
        }
    }
    return false;
}

bool check_collision_singe2(Singe singe1, Singe singe2)
{
    Rectangle s1;
    s1.x = singe1.position.x;
    s1.y = singe1.position.y;
    s1.height = singe1.taille.x;
    s1.width = singe1.taille.y;

    Rectangle s2;
    s2.x = singe2.position.x;
    s2.y = singe2.position.y;
    s2.height = singe2.taille.x;
    s2.width = singe2.taille.y;

    return CheckCollisionRecs(s1, s2);
}