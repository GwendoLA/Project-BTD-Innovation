#include "raylib.h"
#include <iostream>
#include "menu.cpp"
#include "ballon.cpp"
#include <string.h>
#include "singe.cpp"
#include "bouton.cpp"
#include "interface.cpp"
#include "constantes.h"
#include "fleche.cpp"

int main(void)
{
    // Initialisation fenetre
    InitWindow(screenWidth, screenHeight, " Monkey Tower Defense ");

    Image im_fleche = LoadImage(PATH_FLECHE);

    Image im_singe = LoadImage(PATH_SINGE1);
    Image im_singe_bis = LoadImage(PATH_SINGE1);

    Image im_singe2 = LoadImage(PATH_SINGE2);
    Image im_singe2_bis = LoadImage(PATH_SINGE2);

    ImageResize(&im_singe, 150, 150);
    ImageResize(&im_singe_bis, 100, 100);
    ImageResize(&im_singe2, 150, 150);
    ImageResize(&im_singe2_bis, 100, 100);

    Texture2D texture_fleche = LoadTextureFromImage(im_fleche);
    Texture2D texture = LoadTextureFromImage(im_singe);
    Texture2D textsinge = LoadTextureFromImage(im_singe_bis);
    Texture2D texture2 = LoadTextureFromImage(im_singe2);
    Texture2D textsinge2 = LoadTextureFromImage(im_singe2_bis);

    SetTargetFPS(60);

    bool need_to_close = menu_start();
    //--------------------------------------------------------------------------------------
    int round = 49;
    int vies = 40;
    int index = 0;
    int money = MONEY_DEPART;
    int nb_ballons = 0;
    int ballons_cree = 0;
    int compteur = 0;
    bool start_round = false;
    int ballons_vivants = 0;
    bool victoire = false;
    bool defaite = false;

    // création de la liste de stockage des ballons
    Ballon ballons[10000] = {};

    // liste chemin
    Rectangle chemin[36] = {};

    Button bouton1 = creer_bouton({13 * SQUARE_SIZE, 3.8 * SQUARE_SIZE}, {2.25 * SQUARE_SIZE, 0.75 * SQUARE_SIZE}, "250 MONEY");
    Button bouton2 = creer_bouton({13 * SQUARE_SIZE, 6.5 * SQUARE_SIZE}, {2.25 * SQUARE_SIZE, 0.75 * SQUARE_SIZE}, "400 MONEY");
    Button bouton_round = creer_bouton({13 * SQUARE_SIZE, 7.75 * SQUARE_SIZE}, {2.25 * SQUARE_SIZE, 0.75 * SQUARE_SIZE}, "START ROUND");

    // On crée henry, le singe de transition

    Singe henry = creer_singe({0.0}, 120);
    Singe marc = creer_singe({0.0}, 60);

    // création de la liste de stockage des singes
    Singe singes[1000] = {};
    int nb_singes = 0;

    // création de la liste de stockage des fleches
    Fleche fleches[10000] = {};
    int nb_fleches = 0;

    bool pause = false; // jeu en pause ou non, avec la barre espace

    creation_chemin(chemin);

    // Main game loop
    while (!need_to_close && victoire == false && defaite == false)
    { // Detect window close button or ESC key
        need_to_close = WindowShouldClose();
        if (IsKeyPressed(KEY_SPACE))
            pause = !pause;
        if (!pause)
        {
            index++;
            compteur++;

            for (int s = 0; s < nb_singes; s++)
            {
                if (singes[s].fatigue > 0)
                {
                    singes[s].fatigue -= 1;
                }
            }

            BeginDrawing();

            ClearBackground(COLOR_BACKGROUND);

            // draw_lignes();

            Rectangle rect_affichage{12.5 * SQUARE_SIZE, 0.25 * SQUARE_SIZE, 3.25 * SQUARE_SIZE, 8.5 * SQUARE_SIZE};
            DrawRectangle(12.5 * SQUARE_SIZE, 0.2 * SQUARE_SIZE, 3.25 * SQUARE_SIZE, 8.55 * SQUARE_SIZE, {185, 206, 29, 255});
            DrawText(TextFormat(" ROUND : %4i \n MONEY : %4i \n VIES : %4i", round, money, vies), 1250, 30, 40, COLOR_TEXT);
            DrawTexture(texture, 13.25 * SQUARE_SIZE, 2.25 * SQUARE_SIZE, WHITE);
            DrawTexture(texture2, 13.25 * SQUARE_SIZE, 5 * SQUARE_SIZE, WHITE);
            dessiner_bouton(bouton1, 30);
            dessiner_bouton(bouton2, 30);
            dessiner_bouton(bouton_round, 25);

            for (int i = 0; i < 36; i++)
            {
                DrawRectangleRec(chemin[i], {189, 196, 134, 255});
                DrawRectangleRec({chemin[i].x + 1, chemin[i].y + 1, chemin[i].width - 2, chemin[i].height - 2}, {90, 98, 65, 255});
            }

            if (start_round)
            {
                if (compteur % (60 - round) == 0 & ballons_cree < nb_ballons)
                {
                    for (int i = 0; i < (round / 5) + 1; i++)
                    {
                        if (ballons_cree < nb_ballons)
                        {
                            Ballon ballon2 = creer_ballon({50, 350}, 30);
                            ballons[ballons_cree] = ballon2;
                            ballons_cree += 1;
                        }
                    }
                }

                if (ballons_vivants <= 0 && round == 50)
                {
                    victoire = true;
                }
            }

            // Verif si le bouton est cliqué
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                if (detect_click(bouton1) && money - 250 >= 0)
                {
                    henry = creer_singe(GetMousePosition(), 120);
                    henry.etat = true;
                }

                else if (henry.etat == true)
                {
                    bool coll_singe = false;
                    henry.etat = false;
                    for (Singe singe : singes)
                    {
                        if (check_collision_singe2(henry, singe))
                        {
                            coll_singe = true;
                            break;
                        }
                    }
                    if (check_collision_singe(henry, chemin) == false && CheckCollisionPointRec({GetMousePosition().x + 50, GetMousePosition().y + 50}, rect_affichage) == false & coll_singe == false)
                    {
                        Singe singe1 = henry;
                        singe1.etat = true;
                        singes[nb_singes] = singe1;
                        nb_singes++;
                        money -= 250;
                    }
                }

                if (detect_click(bouton2) && money - 400 >= 0)
                {
                    marc = creer_singe(GetMousePosition(), 60);
                    marc.etat = true;
                }

                else if (marc.etat == true)
                {
                    bool coll_singe = false;
                    marc.etat = false;
                    for (Singe singe : singes)
                    {
                        if (check_collision_singe2(marc, singe))
                        {
                            coll_singe = true;
                            break;
                        }
                    }
                    if (check_collision_singe(marc, chemin) == false && CheckCollisionPointRec({GetMousePosition().x + 50, GetMousePosition().y + 50}, rect_affichage) == false & coll_singe == false)
                    {
                        Singe singe1 = marc;
                        singe1.etat = true;
                        singes[nb_singes] = singe1;
                        nb_singes++;
                        money -= 400;
                    }
                }

                if (detect_click(bouton_round))
                {
                    bool fin_round = true;
                    for (Ballon ballon : ballons)
                    {

                        if (ballon.etat == 1)
                        {
                            fin_round = false;
                            break;
                        }
                    }

                    if (fin_round & ballons_cree == nb_ballons)
                    {
                        start_round = true;
                        ballons_cree = 0;
                        round += 1;
                        nb_ballons += BALON_PAR_ROUND;
                        ballons_vivants = nb_ballons;
                        nb_fleches = 0;
                    }
                }
            }
            if (henry.etat == true)
            {
                Vector2 milieu_singe = {GetMousePosition().x - 50, GetMousePosition().y - 50};
                henry.position = milieu_singe;
                dessiner_singe(henry, textsinge);
            }

            if (marc.etat == true)
            {
                Vector2 milieu_singe = {GetMousePosition().x - 50, GetMousePosition().y - 50};
                marc.position = milieu_singe;
                dessiner_singe(marc, textsinge2);
            }

            for (int i = 0; i < ballons_cree; i++)
            {
                dessiner_ballon(ballons[i]);
            }
            for (int i = 0; i < ballons_cree; i++)
            {
                dessiner_ballon2(ballons[i]);
            }

            for (int i = 0; i < ballons_cree; i++)
            {
                Ballon B = ballons[i];
                Vector2 fin = {(SQUARE_SIZE * 10) + SQUARE_SIZE / 2, SQUARE_SIZE / 2};
                if (B.position.x == fin.x && B.position.y == fin.y && B.etat == 1)
                {
                    vies -= 1; // si un ballon arrive à la fin du chemin, on perd 1 vie
                    ballons_vivants -= 1;
                    if (vies == 0)
                    {
                        defaite = true;
                    }
                }
                ballons[i] = mouv(ballons[i], chemin, nbr_rectangle, pause);
            }

            for (int i = 0; i < nb_fleches; i++)
            {
                mouv_fleche(fleches[i]);
            }

            for (int s = 0; s < nb_singes; s++)
            {
                bool singe_tir = false;
                for (int i = 0; i < nb_ballons; i++)
                {
                    if (ballons[i].etat == 1)
                    {
                        if ((check_coll_s_b(singes[s], ballons[i])) && singes[s].fatigue == 0)
                        {
                            if (!singe_tir)
                            {
                                Fleche fleche1 = creer_fleche({singes[s].position.x + ((singes[s].taille.x + 20) / 2), singes[s].position.y + ((singes[s].taille.y + 20) / 2)}, ballons[i], texture_fleche);
                                singe_tir = true;
                                fleches[nb_fleches] = fleche1;
                                nb_fleches++;
                                singes[s].fatigue += singes[s].fatigue_tir;
                            }
                        }

                        for (int j = 0; j < nb_fleches; j++)
                        {
                            if (fleches[j].cible == 0 && fleches[j].etat != 0)
                            {
                                check_coll_b_f(fleches[j], ballons[i]);
                            }
                            if (fleches[j].cible == 1 && ballons[i].etat == 1)
                            {
                                ballons[i].etat = 0;
                                fleches[j].cible = 2;
                                fleches[j].etat = 0;
                                money += 1; // dès qu'on éclate un ballon, on gagne 1 Money
                                ballons_vivants -= 1;
                                if (ballons_vivants <= 0)
                                {
                                    money += 100 - (round - 1);
                                    if (round == 50)
                                    {
                                        victoire = true;
                                    }
                                }
                            }
                            if (fleches[j].cible == 1 && ballons[i].etat == 1)
                            {
                                fleches[j].etat = 1;
                                fleches[j].cible = 0;
                            }
                            if (fleches[j].cible == 2)
                            {
                                fleches[j].etat = 0;
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < nb_singes; i++)
            {
                if (singes[i].fatigue_tir == 120)
                {
                    dessiner_singe(singes[i], textsinge);
                }

                if (singes[i].fatigue_tir == 60)
                {
                    dessiner_singe(singes[i], textsinge2);
                }
            }

            for (int i = 0; i < nb_fleches; i++)
            {
                dessiner_fleche(fleches[i]);
            }

            EndDrawing();
        }
    }
    UnloadImage(im_fleche);
    UnloadTexture(texture_fleche); // Unload texture from VRAM
    UnloadTexture(texture);        // Unload texture from VRAM
    UnloadImage(im_singe);
    UnloadTexture(textsinge); // Unload texture from VRAM
    UnloadImage(im_singe_bis);
    UnloadTexture(texture2); // Unload texture from VRAM
    UnloadImage(im_singe2);
    UnloadTexture(textsinge2); // Unload texture from VRAM
    UnloadImage(im_singe2_bis);

    if (!need_to_close && victoire)
    {
        // a faire
        menu_victoire();
    }

    if (!need_to_close && defaite)
    {
        // a faire
        menu_defaite();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
