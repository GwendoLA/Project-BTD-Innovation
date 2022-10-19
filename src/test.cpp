#include "raylib.h"
#include <iostream>
#include "menu.cpp"
#include <string.h>

#define SQUARE_SIZE 100

static int screenWidth = 1600;
static int screenHeight = 900;
int compteur_chemin = 0;

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

typedef struct Singe
{
    bool etat;
    Vector2 position;
    Vector2 taille;
    Color color;
    Texture texture; 
} Singe;

Singe creer_singe(Vector2 position)
{
    Singe singe;
    singe.etat = false;
    singe.position = position;
    singe.taille = {100, 100};
    singe.color = RED;
    return singe;
}

void dessiner_singe(Singe singe, Texture text)
{
    
    DrawTexture(text, singe.position.x, singe.position.y, WHITE);
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

void dessiner_bouton(Button bouton)
{
    DrawRectangleV(bouton.position, bouton.taille, GRAY);
    DrawText(TextFormat(bouton.ecriture), bouton.position.x + 0.25 * SQUARE_SIZE, bouton.position.y + 0.25 * SQUARE_SIZE, 30, WHITE);
}

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

int main(void)
{
    // Initialisation fenetre
    InitWindow(screenWidth, screenHeight, " classic game: missile commander");
    Image im_singe = LoadImage("C:/Users/maeva/OneDrive/Images/singe3.png");
    Image im_singe2 = LoadImage("C:/Users/maeva/OneDrive/Images/singe3.png");
    ImageResize(&im_singe, 150,150);
    ImageResize(&im_singe2, 100, 100);
    Texture2D texture = LoadTextureFromImage(im_singe);
    Texture2D textsinge = LoadTextureFromImage(im_singe2);
    

    SetTargetFPS(60);

    menu();
    //--------------------------------------------------------------------------------------
    int index = 0;
    int money = 400;

    // liste chemin
    Rectangle chemin[36] = {};

    Button bouton1 = creer_bouton({13.15* SQUARE_SIZE, 3.8 * SQUARE_SIZE}, {2 * SQUARE_SIZE, 0.75*SQUARE_SIZE}, "20 MONEY");

    // On crée henry, le singe de transition

    Singe henry = creer_singe({0.0});


    // création de la liste de stockage des singes
    Singe singes[100] = {};
    int nb_singes = 0;

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
        // dessiner_bouton(bouton1);
        index++;
        std::cout << '\r' << index;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int i = 0; i < screenWidth / SQUARE_SIZE + 1; i++)
        {
            DrawLineV({(float)(SQUARE_SIZE * i), 0.0}, {(float)(SQUARE_SIZE * i), (float)(screenHeight)}, LIGHTGRAY);
        }

        for (int i = 0; i < screenHeight / SQUARE_SIZE + 1; i++)
        {
            DrawLineV({0.0, (float)(SQUARE_SIZE * i)}, {(float)(screenWidth), (float)(SQUARE_SIZE * i)}, LIGHTGRAY);
        }

        DrawRectangle(12.5 * SQUARE_SIZE, 0.25 * SQUARE_SIZE, 3.25 * SQUARE_SIZE, 8.5 * SQUARE_SIZE, LIGHTGRAY);
        DrawText(TextFormat(" ROUND : %4i \n MONEY : %4i \n VIES : %4i", index, money, -index), 1250, 30, 40, MAGENTA);
        DrawTexture(texture, 13.25 * SQUARE_SIZE, 2.25* SQUARE_SIZE, WHITE);
        dessiner_bouton(bouton1);

        // DrawRectangle(0, 100, 300, 80, DARKGRAY);  // gauche, haut, longueur, largeur
        for (int i = 0; i < 36; i++)
        {
            DrawRectangleRec(chemin[i], DARKGRAY);
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
                Singe singe1 = henry;
                if (check_collision_singe(singe1, chemin) == false)
                {
                    singe1.etat = true;
                    singes[nb_singes] = singe1;
                    nb_singes++;
                    money -= 20;
                }
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

        // DrawRectangle(300, 400, 300, 80, DARKGRAY);
        // DrawRectangle(600, 180, 80, 300, DARKGRAY);
        // DrawRectangle(600, 100, 500, 80, DARKGRAY);
        // DrawRectangle(1100, 100, 80, 550, DARKGRAY);

        EndDrawing();
    }
    UnloadTexture(texture); // Unload texture from VRAM
    UnloadImage(im_singe);
    UnloadTexture(textsinge); // Unload texture from VRAM
    UnloadImage(im_singe2);
    
    
    CloseWindow(); // Close window and OpenGL context

    std::cout << "Goodbye World!";
    return 0;
}
