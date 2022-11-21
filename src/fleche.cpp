#include "raylib.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "constantes.h"

#define M_PI 3.14159265358979323846

typedef struct Fleche
{                // Structure Fleche
    int etat;    // visible (1) ou non (0)
    int cible;   // cible pas touchée (0), cible touchée (1), a atteint les bords (2)
    float dir_x; // sa direction vers sa cible, en x
    float dir_y; // sa sirection vers sa cible, en y
    Vector2 position;
    Vector2 size;
    Color color;
    Texture texture;
} Fleche;

Fleche creer_fleche(Vector2 position, Ballon B, Texture texture)
{
    Fleche F;
    F.etat = 1;
    F.cible = 0;
    F.dir_x = B.position.x - position.x;
    F.dir_y = B.position.y - position.y;
    F.position = position;
    F.size = {60, 15};
    F.color = PINK;
    F.texture = texture;
    return F;
}

float signaz(float &num)
{
    if (num > 0.)
    {
        return 1.;
    }
    if (num == 0.)
    {
        return 0.;
    }
    if (num < 0.)
    {
        return -1.;
    }
    return 0;
}
void dessiner_fleche(Fleche &F)
{ // Pour dessiner un ballon, en fonction position rayon et couleur
    if (F.etat == 1)
    {
        Vector2 F_center = {((F.size.x) / 2), ((F.size.y) / 2)};
        Rectangle Rect_F;
        Rect_F.x = F.position.x;
        Rect_F.y = F.position.y;
        Rect_F.height = F.size.y;
        Rect_F.width = F.size.x;
        float angle = atan((F.dir_y) / (F.dir_x)) + M_PI / 2;
        // double pi = M_PI;
        // angle = (angle * 180.) / pi;

        // if (F.dir_x<0 && F.dir_y<0){
        //     angle=angle;
        // }
        // if (F.dir_x > 0 && F.dir_y < 0)
        // {
        //     angle=angle;
        // }
        int indice = 0;
        if (F.dir_x > 0 && F.dir_y > 0)
        {
            // angle += 180.;
            // angle += M_PI/2;
            indice = 1;
        }
        if (F.dir_x < 0 && F.dir_y > 0)
        {
            // angle += 180.;
            angle += M_PI;
            indice = 2;
        }
        if (F.dir_x > 0 && F.dir_y < 0)
        {
            // angle += 180.;
            // angle += M_PI;
            indice = 1;
        }
        if (F.dir_x < 0 && F.dir_y < 0)
        {
            // angle += 180.;
            angle += M_PI;
            indice = 2;
        }

        // DrawRectanglePro(Rect_F, F_center, angle, F.color);

        double angle2 = atan((F.dir_y) / (F.dir_x));
        Vector2 F_center2 = {F.size.x / 2, F.size.y / 2};
        Vector2 points[4] = {
            {-F_center2.x, -F_center2.y},
            {F_center2.x, -F_center2.y},
            {-F_center2.x, F_center2.y},
            {F_center2.x, F_center2.y}};
        float distances = sqrt(pow(F_center2.x, 2) + pow(F_center2.y, 2));
        float current_angle2 = abs(atan(points[indice].y / points[indice].x));
        Vector2 point_arrive = {(float)(F.position.x + signaz(points[indice].x) * distances * cos(signaz(points[indice].x) * signaz(points[indice].y) * angle2 + current_angle2)),
                                (float)(F.position.y + signaz(points[indice].y) * distances * sin(signaz(points[indice].x) * signaz(points[indice].y) * angle2 + current_angle2))};
        DrawTextureEx(F.texture, point_arrive, 180 * angle / M_PI, 0.1, WHITE);
    }
}

void mouv_fleche(Fleche &F)
{
    double distance = sqrt(pow(F.dir_x, 2) + pow(F.dir_y, 2));
    F.position.x += (F.dir_x / distance) * 20;
    F.position.y += (F.dir_y / distance) * 20;
}

bool check_coll_s_b(Singe S, Ballon B)
{
    Vector2 S_center = {(S.position.x + (S.taille.x / 2)), (S.position.y + (S.taille.y / 2))};

    if (CheckCollisionCircles(S_center, S.range, B.position, B.radius))
    {
        Vector2 S_center = {S.position.x + ((S.taille.x) / 2), S.position.y + ((S.taille.y) / 2)};
        return true;
    }
    return false;
}

Fleche check_coll_b_f(Fleche F, Ballon B)
{

    double angle = atan((F.dir_y) / (F.dir_x));
    Vector2 F_center = {F.size.x / 2, F.size.y / 2};
    Vector2 points[4] = {
        {-F_center.x, -F_center.y},
        {F_center.x, -F_center.y},
        {-F_center.x, F_center.y},
        {F_center.x, F_center.y}};
    /// on calcule uniquement une valeur des distances car elles sont théoriquement toutes les mêmes.
    // float distances[4] = {};
    // for (int i = 0; i < 4; i++)
    // {
    //     distances[i] = sqrt(pow(points[i].x, 2) + pow(points[i].y, 2));
    // }
    float distances = sqrt(pow(F_center.x, 2) + pow(F_center.y, 2));
    Vector2 points_arrive[4] = {};
    for (int i = 0; i < 4; i++)
    {
        float current_angle = abs(atan(points[i].y / points[i].x));
        points_arrive[i] = {(float)(F.position.x + signaz(points[i].x) * distances * cos(signaz(points[i].x) * signaz(points[i].y) * angle + current_angle)),
                            (float)(F.position.y + signaz(points[i].y) * distances * sin(signaz(points[i].x) * signaz(points[i].y) * angle + current_angle))};
    }
    for (int i = 0; i < 4; i++)
    {
        // DrawCircle(points_arrive[i].x, points_arrive[i].y, 5, VIOLET);
        if (CheckCollisionPointCircle(points_arrive[i], B.position, B.radius))
        {
            F.etat = 0;
            F.cible = 1;
        }
    }

    // DrawRectangleRec(Rect_F, PURPLE);

    // if (CheckCollisionCircleRec(B.position, B.radius, Rect_F))
    // {
    //     F.etat = 0;
    //     F.cible = 1;
    // }
    if ((F.position.x <= 0) || (F.position.y <= 0) || (F.position.x >= GetScreenWidth()) || (F.position.y >= GetScreenHeight()))
    {
        F.etat = 0;
        F.cible = 2;
    }
    return F;
}
