// #include "../../dep/include/raylib.h"
#include "raylib.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

////#include "../src/constantes.h"

#define SQUARE_SIZE 100

#define screenWidth 1600
#define screenHeight 900

#define MONEY_DEPART 400

#define nbr_rectangle 36 // nombre de rectangle du chemin

////

// #include "raylib.h"
// #include <iostream>

//// #include "../src/menu.cpp"

void menu()
{
    while (!WindowShouldClose() && !(IsKeyPressed(KEY_ENTER)))
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Bienvenue sur notre version de", 400, 200, 50, BLUE);
        DrawText("Bloons Tower Defense", 500, 250, 50, BLUE);
        DrawText("By Maëva, Aurélien and Alice", 650, 300, 20, DARKGRAY);
        DrawText("Press ENTER to start the game", 400, 500, 50, BLACK);
        EndDrawing();
    }
}

////

// #include "../src/ballon.cpp"
#include <string.h>
// #include "../src/singe.cpp"

//// #include "../src/bouton.cpp"

// #include "raylib.h"
// #include <iostream>
#include <stdlib.h>
// #include "constantes.h"

typedef struct Button
{
    bool etat;
    Vector2 position;
    Vector2 taille;
    Color color;
    char ecriture[30];
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

////

//// #include "../src/interface.cpp"

// #include "raylib.h"
// #include <iostream>
// #include <stdlib.h>
// #include "constantes.h"

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

////

#define LEN_LISTS 1000

typedef struct Ballon
{ // Structure Ballon
    int etat;
    Vector2 position;
    int vitx;
    int vity;
    int radius;
    int rect;
    Color color;

    friend std::ostream &operator<<(std::ostream &os, Ballon const &a)
    {
        return os << "Ballon "
                  << "{ "
                  << a.etat << ", "
                  << "Vector2 "
                  << "{ " << a.position.x << ", "
                  << a.position.y << " }"
                  << ", "
                  << a.vitx << ", "
                  << a.vity << ", "
                  << a.radius << ", "
                  << a.rect << ", "
                  << "Color "
                  << "{ " << int(a.color.r) << ", "
                  << int(a.color.g) << ", "
                  << int(a.color.b) << ", "
                  << int(a.color.a) << " }"
                  << " }"
                  << " }";
    }
} Ballon;

Ballon creer_ballon(Vector2 position, int radius)
{ // Pour créer un objet Ballon
    Ballon ballon;
    ballon.etat = 1;
    ballon.position = position;
    ballon.vitx = 2; // choix de la vitesse en x du ballon, que pour cet exemple
    ballon.vity = 2; // choix de la vitesse en y du ballon, que pour cet exemple
    ballon.radius = radius;
    ballon.rect = 1;
    ballon.color = RED;
    return ballon;
}

void dessiner_ballon(Ballon ballon)
{ // Pour dessiner un ballon, en fonction position rayon et couleur
    if (ballon.etat == 1)
    {
        DrawCircleV(ballon.position, ballon.radius, ballon.color);
    }
}
// void dessiner_ballon(Ballon ballon)
// { // Pour dessiner un ballon, en fonction position rayon et couleur
//     if (ballon.etat == 1)
//     {
//         DrawCircleV(ballon.position, ballon.radius, ballon.color);
//         DrawRectangleV(ballon.position, {40, 40}, ballon.color);
//     }
// }

Vector4 bouger_ballon(Ballon ballon, Rectangle r1, Rectangle r2)
{ // Pour bouger le ballon d'un rectangle à un autre
    float x1 = r1.x + (r1.width) / 2;
    float y1 = r1.y + (r1.height) / 2;
    float x2 = r2.x + (r2.width) / 2;
    float y2 = r2.y + (r2.height) / 2;
    float diff_x = x2 - x1;
    float diff_y = y2 - y1;
    return {diff_x, diff_y, x2, y2};
}
Ballon mouv(Ballon B, Rectangle liste_R[36], int nbr_r, bool pause)
{
    int i = 0;
    int j = B.rect;
    if (i != j && j < nbr_r)
    { // i et j permettent les itérations
        i = j - 1;
        Vector4 bouge = bouger_ballon(B, liste_R[i], liste_R[i + 1]);
        if (B.position.x != bouge.z)
        {
            B.position.x += (bouge.x / 50);
        }
        if (B.position.y != bouge.w)
        {
            B.position.y += (bouge.y / 50);
        }
        if ((B.position.x == bouge.z) && (B.position.y == bouge.w))
        {
            j += 1;
            B.rect = j;
        }
        return B;
    }
    else
    {
        return B; // le ballon est à la fin du chemin -> fin du round
    }
}

typedef struct Singe
{
    bool etat;
    Vector2 position;
    Vector2 taille;
    int range; // zone de detection des ballons
    int ang;
    Color color;
    Texture texture;
    int last_time_shoot;

    friend std::ostream &operator<<(std::ostream &os, Singe const &a)
    {
        return os << "Singe "
                  << "{ "
                  << a.etat << ", "
                  << "Vector2 "
                  << "{ " << a.position.x << ", "
                  << a.position.y << " }"
                  << ", "
                  << "Vector2 "
                  << "{ " << a.taille.x << ", "
                  << a.taille.y << " }"
                  << ", "
                  << a.range << ", "
                  << a.ang << ", "
                  << "Color "
                  << "{ " << int(a.color.r) << ", "
                  << int(a.color.g) << ", "
                  << int(a.color.b) << ", "
                  << int(a.color.a) << " }"
                  << " }"
                  << ", "
                  << "Texture "
                  << "{ " << a.texture.id << ", "
                  << a.texture.width << ", "
                  << a.texture.height << ", "
                  << a.texture.mipmaps << ", "
                  << a.texture.format << " }"
                  << " }"
                  << " }";
    }
} Singe;

Singe creer_singe(Vector2 position)
{
    Singe singe;
    singe.etat = false;
    singe.position = position;
    singe.taille = {100, 100};
    singe.range = 200; // choix du range par defaut
    singe.ang = 10;
    singe.color = RED;
    singe.last_time_shoot = 0;
    return singe;
}

// Singe creer_singe(Vector2 position)
// {
//     Singe singe;
//     singe.etat = false;
//     singe.position = position;
//     singe.taille = {50, 100};
//     singe.range = 200; // choix du range par defaut
//     singe.ang = 10;
//     singe.color = RED;
//     singe.last_time_shoot = 0;
//     return singe;
// }

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

void dessiner_singe(Singe &S)
{
    S.ang += 5;
    Vector2 S_center = {((S.taille.x) / 2), ((S.taille.y) / 2)};

    Rectangle Rect_S;
    Rect_S.x = S.position.x;
    Rect_S.y = S.position.y;
    Rect_S.height = S.taille.y;
    Rect_S.width = S.taille.x;
    DrawRectanglePro(Rect_S, S_center, S.ang, GREEN);
}
void dessiner_singe(Singe &singe, Texture text)
{

    dessiner_singe(singe);

    DrawTexture(text, singe.position.x, singe.position.y, WHITE);

    // Rectangle some;
    // some.x = singe.position.x;
    // some.y = singe.position.y;
    // some.width = text.width;
    // some.height = text.height;
    // DrawTexturePro(text, some, some, singe.position, singe.ang, WHITE);
}

typedef struct Fleche
{                // Structure Fleche
    int etat;    // visible (1) ou non (0)
    int cible;   // cible pas touchée (0), cible touchée (1), a atteint les bords (2)
    float dir_x; // sa direction vers sa cible, en x
    float dir_y; // sa sirection vers sa cible, en y
    Vector2 position;
    Vector2 size;
    Color color;

    friend std::ostream &operator<<(std::ostream &os, Fleche const &a)
    {
        return os << "Fleche "
                  << "{ "
                  << a.etat << ", "
                  << a.cible << ", "
                  << a.dir_x << ", "
                  << a.dir_y << ", "
                  << "Vector2 "
                  << "{ " << a.position.x << ", "
                  << a.position.y << " }"
                  << ", "
                  << "Vector2 "
                  << "{ " << a.size.x << ", "
                  << a.size.y << " }"
                  << ", "
                  << "Color "
                  << "{ " << int(a.color.r) << ", "
                  << int(a.color.g) << ", "
                  << int(a.color.b) << ", "
                  << int(a.color.a) << " }"
                  << " }"
                  << " }";
    }
} Fleche;

// Fleche creer_fleche(Vector2 position)
// { // Pour créer un objet Ballon
//     Fleche F;
//     F.etat = 0;
//     F.cible = 0;
//     F.dir_x = 0;
//     F.dir_y = 0;
//     F.position = position;
//     F.size = {80, 30};
//     F.color = PINK;
//     return F;
// }
Fleche creer_fleche(Vector2 position, Vector2 direction)
{ // Pour créer un objet Ballon
    Fleche F;
    F.etat = 1;
    F.cible = 0;
    F.dir_x = direction.x - position.x;
    F.dir_y = direction.y - position.y;
    F.position = position;
    F.size = {80, 30};
    F.color = PINK;
    return F;
}

void dessiner_fleche(Fleche F)
{ // Pour dessiner un ballon, en fonction position rayon et couleur
    Vector2 F_center = {((F.size.x) / 2), ((F.size.y) / 2)};

    Rectangle Rect_F;
    Rect_F.x = F.position.x;
    Rect_F.y = F.position.y;
    Rect_F.height = F.size.y;
    Rect_F.width = F.size.x;
    std::cout << F;
    std::cout << " | ";
    float angle = atan((F.dir_y) / (F.dir_x));
    std::cout << angle;
    std::cout << "  ";
    double pi = M_PI;
    angle = float((angle * 180.) / pi);
    std::cout << angle;
    std::cout << "  ";

    if (F.dir_x < 0 && F.dir_y < 0)
    {
        angle += 180;
        // std::cout << angle;
        // std::cout << " RED";
        // DrawRectanglePro(Rect_F, F_center, 0, DARKGREEN);
        // DrawRectanglePro(Rect_F, {0, 0}, 0, DARKBLUE);
        // DrawRectanglePro(Rect_F, F_center, angle, F.color);
        // DrawPoly({F.position.x, F.position.y}, 3, 25, angle, RED);
    }
    if (F.dir_x > 0 && F.dir_y < 0)
    {
        // angle *= -1;
        // std::cout << angle;
        // std::cout << " GREEN";
        // DrawRectanglePro(Rect_F, F_center, 0, DARKGREEN);
        // DrawRectanglePro(Rect_F, {0, 0}, 0, DARKBLUE);
        // DrawRectanglePro(Rect_F, F_center, angle, F.color);
        // DrawPoly({F.position.x, F.position.y}, 3, 25, angle, GREEN);
    }
    if (F.dir_x > 0 && F.dir_y > 0)
    {
        // angle *= -1;
        // std::cout << angle;
        // std::cout << " BLUE";
        // DrawRectanglePro(Rect_F, F_center, 0, DARKGREEN);
        // DrawRectanglePro(Rect_F, {0, 0}, 0, DARKBLUE);
        // DrawRectanglePro(Rect_F, F_center, angle, F.color);
        // DrawPoly({F.position.x, F.position.y}, 3, 25, angle, BLUE);
    }
    if (F.dir_x < 0 && F.dir_y > 0)
    {
        angle -= 180;
        // std::cout << angle;
        // std::cout << " BLACK";
        // DrawRectanglePro(Rect_F, F_center, 0, DARKGREEN);
        // DrawRectanglePro(Rect_F, {0, 0}, 0, DARKBLUE);
        // DrawRectanglePro(Rect_F, F_center, angle, F.color);
        // DrawPoly({F.position.x, F.position.y}, 3, 25, angle, BLACK);
    }
    std::cout << angle;
    // std::cout << " BLACK";
    DrawRectanglePro(Rect_F, F_center, 0, DARKGREEN);
    DrawRectanglePro(Rect_F, {0, 0}, 0, DARKBLUE);
    DrawRectanglePro(Rect_F, F_center, angle, F.color);
    DrawPoly({F.position.x, F.position.y}, 3, 25, angle, BLACK);

    std::cout << '\n';
    // }
}

// check quand le ballon arrive dans le range du singe
bool check_coll_s_b(Singe S, Ballon B)
{
    if (CheckCollisionCircles(S.position, S.range, B.position, B.radius))
    {
        Vector2 S_center = {S.position.x + ((S.taille.x) / 2), S.position.y + ((S.taille.y) / 2)};
        return true;
    }
    return false;
}

Fleche check_coll_b_f(Fleche &F, Ballon &B, Singe &S)
{
    Vector2 S_center = {S.position.x + ((S.taille.x) / 2), S.position.y + ((S.taille.y) / 2)};
    Rectangle Rect_F;
    Rect_F.x = F.position.x;
    Rect_F.y = F.position.y;
    Rect_F.height = F.size.y;
    Rect_F.width = F.size.x;

    F.position.x += (F.dir_x / 80);
    F.position.y += (F.dir_y / 80);

    if (CheckCollisionCircleRec(B.position, B.radius, Rect_F))
    {
        F.etat = 0;
        F.cible = 1;
        B.etat = 0;
    }
    if ((F.position.x <= 0) || (F.position.y <= 0) || (F.position.x >= GetScreenWidth()) || (F.position.y >= GetScreenHeight()))
    {
        F.etat = 0;
        F.cible = 2;
    }
    return F;
}

void print_list_ballon(Ballon list_ballon[LEN_LISTS], char separator[])
{
    std::cout << "{ ";
    for (int i = 0; i < LEN_LISTS; i++)
    {
        if (list_ballon[i].etat == 1)
        {
            std::cout << list_ballon[i];
            std::cout << separator;
        }
    }
    std::cout << " }";
}

void add_ballon(Ballon list_ballon[LEN_LISTS], Ballon ballon)
{
    for (int i = 0; i < LEN_LISTS; i++)
    {
        if (list_ballon[i].etat != 1)
        {
            list_ballon[i] = ballon;
            break;
        }
    }
    print_list_ballon(list_ballon, ", ");
    std::cout << '\n';
}
void update_ballons(Ballon list_ballon[LEN_LISTS])
{
    for (int i = 0; i < LEN_LISTS; i++)
    {
        if (list_ballon[i].etat == 1)
        {
            list_ballon[i].position.x += list_ballon[i].vitx;
            list_ballon[i].position.y += list_ballon[i].vity;
        }
    }
}
void dessiner_ballons(Ballon list_ballon[LEN_LISTS])
{
    for (int i = 0; i < LEN_LISTS; i++)
    {
        if (list_ballon[i].etat == 1)
        {
            dessiner_ballon(list_ballon[i]);
        }
    }
}

void print_list_fleche(Fleche list_fleche[LEN_LISTS], char separator[])
{
    std::cout << "{ ";
    for (int i = 0; i < LEN_LISTS; i++)
    {
        if (list_fleche[i].etat == 1)
        {
            std::cout << list_fleche[i];
            std::cout << separator;
        }
    }
    std::cout << " }";
}
void add_fleche(Fleche list_fleche[LEN_LISTS], Fleche fleche)
{
    for (int i = 0; i < LEN_LISTS; i++)
    {
        if (list_fleche[i].etat != 1)
        {
            list_fleche[i] = fleche;
            break;
        }
    }
    print_list_fleche(list_fleche, ", ");
    std::cout << '\n';
}

void dessiner_fleches(Fleche list_fleche[LEN_LISTS])
{
    for (int i = 0; i < LEN_LISTS; i++)
    {
        if (list_fleche[i].etat == 1)
        {
            dessiner_fleche(list_fleche[i]);
        }
    }
}

void check_clos_s_bs(Singe &singe, Ballon list_ballons[LEN_LISTS], Fleche list_fleches[LEN_LISTS])
{
    for (int i = 0; i < LEN_LISTS; i++)
    {
        if (list_ballons[i].etat == 1)
        {
            if (check_coll_s_b(singe, list_ballons[i]))
            {
                std::cout << " got colision ";
                std::cout << singe.last_time_shoot;
                if (singe.last_time_shoot == 0)
                {
                    std::cout << " fleche cree ";
                    Fleche some = creer_fleche({singe.position.x + ((singe.taille.x) / 2), singe.position.y + ((singe.taille.y) / 2)}, list_ballons[i].position);
                    add_fleche(list_fleches, some);
                    singe.last_time_shoot = 60;
                }
                for (int j = 0; j < LEN_LISTS; j++)
                {
                    if (list_fleches[j].etat == 1)
                    {
                        std::cout << " found fleche ";
                        list_fleches[j] = check_coll_b_f(list_fleches[j], list_ballons[i], singe);
                    }
                }
            }
        }
    }
}

void ballons_bound(Ballon list_ballons[LEN_LISTS])
{

    for (int i = 0; i < LEN_LISTS; i++)
    {
        if (list_ballons[i].etat == 1)
        {
            if (((list_ballons[i].position.x + list_ballons[i].radius) >= GetScreenWidth()) || (list_ballons[i].position.x <= 0))
                list_ballons[i].vitx *= -1;
            if (((list_ballons[i].position.y + list_ballons[i].radius) >= GetScreenHeight()) || (list_ballons[i].position.y <= 0))
                list_ballons[i].vity *= -1;
        }
    }
}

int main2()
{
    InitWindow(screenWidth, screenHeight, "test collision avec structure");
    SetTargetFPS(60);

    Ballon list_ballons[LEN_LISTS] = {};
    Ballon ballon1 = creer_ballon({650, 50}, 30);
    Ballon ballon2 = creer_ballon({600, 500}, 30);
    Ballon ballon3 = creer_ballon({450, 50}, 30);
    Ballon ballon4 = creer_ballon({50, 50}, 30);
    ballon2.color = BLUE;
    ballon3.color = DARKBLUE;
    add_ballon(list_ballons, ballon1);
    add_ballon(list_ballons, ballon2);
    add_ballon(list_ballons, ballon3);
    add_ballon(list_ballons, ballon4);

    Singe singe1 = creer_singe({250, 250});

    Fleche list_fleches[LEN_LISTS] = {};
    // Fleche fleche1 = creer_fleche({singe1.position.x + ((singe1.taille.x) / 2), singe1.position.y + ((singe1.taille.y) / 2)});
    // Fleche fleche2 = creer_fleche({singe1.position.x + ((singe1.taille.x) / 2), singe1.position.y + ((singe1.taille.y) / 2)});
    // Fleche fleche3 = creer_fleche({singe1.position.x + ((singe1.taille.x) / 2), singe1.position.y + ((singe1.taille.y) / 2)});
    // Fleche fleche4 = creer_fleche({singe1.position.x + ((singe1.taille.x) / 2), singe1.position.y + ((singe1.taille.y) / 2)});
    // add_fleche(list_fleches, fleche1);
    // add_fleche(list_fleches, fleche2);
    // add_fleche(list_fleches, fleche3);
    // add_fleche(list_fleches, fleche4);

    bool pause = false; // jeu en pause ou non, avec la barre espace

    while (!WindowShouldClose())
    {

        BeginDrawing();

        if (IsKeyPressed(KEY_SPACE))
            pause = !pause;
        if (!pause)
        {
            if (singe1.last_time_shoot != 0)
            {
                singe1.last_time_shoot -= 1;
            }
            update_ballons(list_ballons);

            ClearBackground(RAYWHITE);
            ballons_bound(list_ballons);
            check_clos_s_bs(singe1, list_ballons, list_fleches);

            dessiner_singe(singe1);
            dessiner_ballons(list_ballons);
            dessiner_fleches(list_fleches);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

int main(void)
{
    // Initialisation fenetre
    InitWindow(screenWidth, screenHeight, " classic game: missile commander");
    Image im_singe = LoadImage("./src/singe3.png");
    Image im_singe2 = LoadImage("./src/singe3.png");
    ImageResize(&im_singe, 150, 150);
    ImageResize(&im_singe2, 100, 100);
    Texture2D texture = LoadTextureFromImage(im_singe);
    Texture2D textsinge = LoadTextureFromImage(im_singe2);

    SetTargetFPS(60);

    menu();
    //--------------------------------------------------------------------------------------
    int round = 0;
    int index = 0;
    int money = MONEY_DEPART;
    int nbr_ballons = 0;
    int ballons_cree = 0;
    int compteur = 0;
    bool start_round = false;

    // création de la liste de stockage des ballons
    Ballon ballons[LEN_LISTS] = {};
    Fleche fleches[LEN_LISTS] = {};

    // liste chemin
    Rectangle chemin[36] = {};

    Button bouton1 = creer_bouton({13.15 * SQUARE_SIZE, 3.8 * SQUARE_SIZE}, {2 * SQUARE_SIZE, 0.75 * SQUARE_SIZE}, "20 MONEY");
    Button bouton_round = creer_bouton({13 * SQUARE_SIZE, 7.75 * SQUARE_SIZE}, {2.25 * SQUARE_SIZE, 0.75 * SQUARE_SIZE}, "START ROUND");

    // On crée henry, le singe de transition

    Singe henry = creer_singe({0.0});

    // création de la liste de stockage des singes
    Singe singes[LEN_LISTS] = {};
    int nb_singes = 0;

    bool pause = false; // jeu en pause ou non, avec la barre espace

    // Main game loop
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

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        index++;
        compteur++;
        std::cout << '\r' << index;

        BeginDrawing();

        ClearBackground(RAYWHITE);
        for (int i = 0; i < nb_singes; i++)
        {
            check_clos_s_bs(singes[i], ballons, fleches);
            if (singes[i].last_time_shoot != 0)
            {
                singes[i].last_time_shoot -= 1;
            }
        }
        for (int i = 0; i < screenWidth / SQUARE_SIZE + 1; i++)
        {
            DrawLineV({(float)(SQUARE_SIZE * i), 0.0}, {(float)(SQUARE_SIZE * i), (float)(screenHeight)}, LIGHTGRAY);
        }

        for (int i = 0; i < screenHeight / SQUARE_SIZE + 1; i++)
        {
            DrawLineV({0.0, (float)(SQUARE_SIZE * i)}, {(float)(screenWidth), (float)(SQUARE_SIZE * i)}, LIGHTGRAY);
        }

        Rectangle rect_affichage{12.5 * SQUARE_SIZE, 0.25 * SQUARE_SIZE, 3.25 * SQUARE_SIZE, 8.5 * SQUARE_SIZE};
        DrawRectangle(12.5 * SQUARE_SIZE, 0.25 * SQUARE_SIZE, 3.25 * SQUARE_SIZE, 8.5 * SQUARE_SIZE, LIGHTGRAY);
        DrawText(TextFormat(" ROUND : %4i \n MONEY : %4i \n VIES : %4i", round, money, -index), 1250, 30, 40, MAGENTA);
        DrawTexture(texture, 13.25 * SQUARE_SIZE, 2.25 * SQUARE_SIZE, WHITE);
        dessiner_bouton(bouton1, 30);
        dessiner_bouton(bouton_round, 25);

        for (int i = 0; i < 36; i++)
        {
            DrawRectangleRec(chemin[i], DARKGRAY);
        }

        if (start_round)
        {
            if (compteur % 10 == 0 & ballons_cree < nbr_ballons)
            {
                Ballon ballon2 = creer_ballon({50, 350}, 30);
                ballons[ballons_cree] = ballon2;
                ballons_cree += 1;
            }
        }

        // Verif si le bouton est cliqué
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {

            if (detect_click(bouton1))
            {
                henry = creer_singe(GetMousePosition());
                henry.etat = true;
            }

            else if (henry.etat == true)
            {
                henry.position = GetMousePosition();
                henry.etat = false;
                if (check_collision_singe(henry, chemin) == false & CheckCollisionPointRec(GetMousePosition(), rect_affichage) == false & money != 0)
                {
                    Singe singe1 = henry;
                    singe1.etat = true;
                    singes[nb_singes] = singe1;
                    nb_singes++;
                    money -= 20;
                }
            }

            if (detect_click(bouton_round))
            {
                start_round = true;
                ballons_cree = 0;
                round += 1;
                nbr_ballons += 50;
            }
        }

        if (henry.etat == true)
        {
            henry.position = GetMousePosition();
            dessiner_singe(henry, textsinge);
        }

        for (int i = 0; i < nb_singes; i++)
        {
            dessiner_singe(singes[i], textsinge);
        }

        dessiner_fleches(fleches);
        for (int i = 0; i < ballons_cree; i++)
        {
            dessiner_ballon(ballons[i]);
            if (IsKeyPressed(KEY_SPACE))
                pause = !pause;
            if (!pause)
            {
                ballons[i] = mouv(ballons[i], chemin, nbr_rectangle, pause);
            }
        }
        EndDrawing();
    }
    UnloadTexture(texture); // Unload texture from VRAM
    UnloadImage(im_singe);
    UnloadTexture(textsinge); // Unload texture from VRAM
    UnloadImage(im_singe2);

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
