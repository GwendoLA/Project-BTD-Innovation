#include "raylib.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

static int screenWidth = 1000;
static int screenHeight = 900;

typedef struct Ballon { // Structure Ballon
    int etat;
    Vector2 position;
    int vitx;
    int vity;
    int radius;
    int rect;
    Color color; 
} Ballon;

Ballon creer_ballon (Vector2 position, int radius) { // Pour créer un objet Ballon
    Ballon ballon;
    ballon.etat= 1;
    ballon.position= position;
    ballon.vitx=2;  // choix de la vitesse en x du ballon, que pour cet exemple
    ballon.vity=2;  // choix de la vitesse en y du ballon, que pour cet exemple
    ballon.radius= radius;
    ballon.rect=1;
    ballon.color= RED;
    return ballon;
}

void dessiner_ballon (Ballon ballon) { // Pour dessiner un ballon, en fonction position rayon et couleur
    if (ballon.etat==1){
    DrawCircleV(ballon.position,ballon.radius,ballon.color);
    }
}

void bouge_ballon(Ballon &ballon){
    ballon.position.x += ballon.vitx;
    ballon.position.y += ballon.vity;
}

typedef struct Singe{
    bool etat;
    Vector2 position;
    Vector2 taille;
    int range;  // zone de detection des ballons
    int ang;
    Color color;
    Texture texture; 
} Singe;

Singe creer_singe(Vector2 position){
    Singe singe;
    singe.etat = false;
    singe.position = position;
    singe.taille = {50, 50};
    singe.range = 200;  // choix du range par defaut
    singe.ang=10;
    singe.color = RED;
    return singe;
}

void dessiner_singe(Singe &S){
    // S.ang+=5;
    Vector2 S_center = {((S.taille.x)/2),((S.taille.y)/2)};

    Rectangle Rect_S;
    Rect_S.x=S.position.x;
    Rect_S.y=S.position.y;
    Rect_S.height=S.taille.y;
    Rect_S.width=S.taille.x;
    DrawRectanglePro(Rect_S,S_center,S.ang, GREEN);
}

typedef struct Fleche { // Structure Fleche
    int etat;  // visible (1) ou non (0)
    int cible;  // cible pas touchée (0), cible touchée (1), a atteint les bords (2)
    float dir_x;  // sa direction vers sa cible, en x 
    float dir_y;  // sa sirection vers sa cible, en y
    Vector2 position;
    Vector2 size;
    Color color; 
} Fleche;

Fleche creer_fleche (Vector2 position) { // Pour créer un objet Ballon
    Fleche F;
    F.etat= 0; 
    F.cible=0;
    F.dir_x=0;
    F.dir_y=0;
    F.position= position;
    F.size={60,15};
    F.color= PINK;
    return F;
}

void dessiner_fleche (Fleche F) { // Pour dessiner un ballon, en fonction position rayon et couleur
    if (F.etat==1){
        Vector2 F_center = {((F.size.x)/2),((F.size.y)/2)};
        Rectangle Rect_F;
        Rect_F.x=F.position.x;
        Rect_F.y=F.position.y;
        Rect_F.height=F.size.y;
        Rect_F.width=F.size.x;
        double angle = atan((F.dir_y)/(F.dir_x));
        double pi = M_PI ; 
        angle = (angle*180.)/pi ;
        
        // if (F.dir_x<0 && F.dir_y<0){
        //     angle=angle;
        // }
        // if (F.dir_x>0 && F.dir_y<0){
        //     angle=angle;
        // }
        if (F.dir_x>0 && F.dir_y>0){
            angle+=180.;
        }
        if (F.dir_x<0 && F.dir_y>0){
            angle+=180.;
        }
        
        DrawRectanglePro(Rect_F,F_center,angle,F.color);
    }
}


// check quand le ballon arrive dans le range du singe
bool check_coll_s_b(Singe S, Ballon B){
    if (CheckCollisionCircles(S.position,S.range,B.position,B.radius)){
        Vector2 S_center = {S.position.x+((S.taille.x)/2),S.position.y+((S.taille.y)/2)};
        return true;
    }
    return false;
}

Fleche check_coll_b_f(Fleche F, Ballon B, Singe S){
    Vector2 S_center = {S.position.x+((S.taille.x)/2),S.position.y+((S.taille.y)/2)};
    Rectangle Rect_F;
    Rect_F.x=F.position.x;
    Rect_F.y=F.position.y;
    Rect_F.height=F.size.y;
    Rect_F.width=F.size.x;
    if (F.etat==0){  // on calcule une fois la direction que va suivre le ballon
        float mouv_x = B.position.x - S_center.x ;
        float mouv_y = B.position.y - S_center.y ;
        F.dir_x=mouv_x;
        F.dir_y=mouv_y;
        F.etat=1;
    }
    F.position.x+=(F.dir_x/80); 
    F.position.y+=(F.dir_y/80); 

    if (CheckCollisionCircleRec(B.position,B.radius,Rect_F)){
        F.etat=0;
        F.cible=1;    
    }
    if ((F.position.x<=0)||(F.position.y<=0)||(F.position.x>=GetScreenWidth())||(F.position.y>=GetScreenHeight())){
        F.etat=0;
        F.cible=2;
    }
    return F; 
}


int main(){
    InitWindow(screenWidth, screenHeight, "test collision avec structure");
    SetTargetFPS(60);
      
    Ballon ballon1= creer_ballon ({650,50}, 30);
    Ballon ballon2= creer_ballon ({600,500}, 30);
    Ballon ballon3= creer_ballon ({450,50}, 30);
    Ballon ballon4= creer_ballon ({50,50}, 30);
    ballon2.color=BLUE;
    ballon3.color=DARKBLUE;

    Ballon ballons[100] = {};
    ballons[0] = ballon1;
    ballons[1] = ballon2;
    ballons[2] = ballon3;
    ballons[3] = ballon4;


    Singe singe1 = creer_singe({250,250});
    // Fleche fleche1 = creer_fleche({singe1.position.x+((singe1.taille.x)/2),singe1.position.y+((singe1.taille.y)/2)});
    // Fleche fleche2 = creer_fleche({singe1.position.x+((singe1.taille.x)/2),singe1.position.y+((singe1.taille.y)/2)});
    // Fleche fleche3 = creer_fleche({singe1.position.x+((singe1.taille.x)/2),singe1.position.y+((singe1.taille.y)/2)});
    // Fleche fleche4 = creer_fleche({singe1.position.x+((singe1.taille.x)/2),singe1.position.y+((singe1.taille.y)/2)});

    Fleche fleches[100] = {};
    int compteur = 0;

    bool pause = false; // jeu en pause ou non, avec la barre espace
    int nbr_fleches = 0;

    while (!WindowShouldClose()){

        BeginDrawing();
        compteur++;

        if (IsKeyPressed(KEY_SPACE)) pause = !pause; 
        if (!pause) {
            for (int i = 0; i < 4; i++){
                bouge_ballon(ballons[i]);
                if (((ballons[i].position.x + ballons[i].radius) >= GetScreenWidth()) || (ballons[i].position.x <= 0))
                    ballons[i].vitx *= -1;
                if (((ballons[i].position.y + ballons[i].radius) >= GetScreenHeight()) || (ballons[i].position.y <= 0))
                    ballons[i].vity *= -1;
            }

            ClearBackground(RAYWHITE);

            for (int i = 0; i < 4; i++){
                if (ballons[i].etat == 1){
                    if (check_coll_s_b(singe1, ballons[i]) & compteur % 60 == 0){
                        Fleche fleche1 = creer_fleche({singe1.position.x + ((singe1.taille.x) / 2), singe1.position.y + ((singe1.taille.y) / 2)});
                        fleches[nbr_fleches] = fleche1;
                        nbr_fleches++;
                    }

                    for (int j = 0; j < nbr_fleches; j++){
                        if (fleches[j].cible == 0){
                            fleches[j] = check_coll_b_f(fleches[j], ballons[i], singe1);
                        }
                        if (fleches[j].cible == 1){
                            ballons[i].etat = 0;
                            fleches[j].cible = 2;
                            fleches[j].etat = 0;
                        }
                        if (fleches[j].cible == 2){
                            fleches[j].etat = 0;
                        }
                    }
                }
            }

            dessiner_singe(singe1);

            for (int i = 0; i < 4; i++){
                dessiner_ballon(ballons[i]);
            }

            for (int i = 0; i < nbr_fleches; i++){
                dessiner_fleche(fleches[i]);
            }     
                    
        }
        EndDrawing();
    }
    CloseWindow(); 
    return 0;
}