
#include "raylib.h"
#include <iostream>
#include <vector>
 
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

