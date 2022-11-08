
#include "raylib.h"
#include <iostream>
#include <vector>
#include "constantes.h"
 
typedef struct Singe{
    bool etat;
    Vector2 position;
    Vector2 taille;
    int range;  // zone de detection des ballons
    Color color;
    Texture texture; 
} Singe;

Singe creer_singe(Vector2 position){
    Singe singe;
    singe.etat = false;
    singe.position = position;
    singe.taille = {100, 100};
    singe.range = 200;  // choix du range par defaut
    singe.color = RED;
    return singe;
}

void dessiner_singe(Singe singe, Texture text){
    DrawTexture(text, singe.position.x, singe.position.y, WHITE);
}

bool check_collision_singe(Singe singe, Rectangle rectangles[36])
{
    Rectangle s;
    s.x = singe.position.x;
    s.y = singe.position.y;
    s.height = SQUARE_SIZE;
    s.width = SQUARE_SIZE;
    for (int i = 0; i < 36; i++)
    {
        if (CheckCollisionRecs(s, rectangles[i]))
        {
            return true;
        }
    }
    return false;
}