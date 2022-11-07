#include "raylib.h"
#include <iostream>

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

void dessiner_singe(Singe singe){
    DrawRectangle(singe.position.x, singe.position.y, singe.taille.x, singe.taille.y, GREEN);
}

typedef struct Fleche { // Structure Fleche
    int etat;  // visible (1) ou non (0)
    int cible;  // cible pas touchée (0), cible touchée (1), a atteint les bords (2)
    int dir_x;  // sa direction vers sa cible, en x 
    int dir_y;  // sa sirection vers sa cible, en y
    Vector2 position;
    Vector2 size;
    Color color; 
} Fleche;

Fleche creer_fleche (Vector2 position) { // Pour créer un objet Ballon
    Fleche F;
    F.etat= 0; 
    F.cible=0;
    F.dir_x=0;
    F.dir_x=0;
    F.position= position;
    F.size={20,20};
    F.color= PINK;
    return F;
}

void dessiner_fleche (Fleche F) { // Pour dessiner un ballon, en fonction position rayon et couleur
    if (F.etat==1){
    DrawRectangleV(F.position,F.size,F.color);
    }
}

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
    Rect_F.height=F.size.x;
    Rect_F.width=F.size.y;
    if (F.etat==0){  // on calcule une fois la direction que va suivre le ballon
        int mouv_x = B.position.x - S_center.x ;
        int mouv_y = B.position.y - S_center.y ;
        F.dir_x=mouv_x;
        F.dir_y=mouv_y;
        F.etat=1;
    }
    F.position.x+=(F.dir_x/10); 
    F.position.y+=(F.dir_y/10); 

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
    ballon2.color=BLUE;

    Singe singe1 = creer_singe({250,250});
    Fleche fleche1 = creer_fleche({singe1.position.x+((singe1.taille.x)/2),singe1.position.y+((singe1.taille.y)/2)});
    Fleche fleche2 = creer_fleche({singe1.position.x+((singe1.taille.x)/2),singe1.position.y+((singe1.taille.y)/2)});

    bool pause = false; // jeu en pause ou non, avec la barre espace

    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyPressed(KEY_SPACE)) pause = !pause; 
        if (!pause) {
            ballon1.position.x +=ballon1.vitx ;
            ballon1.position.y +=ballon1.vity ;     
            ballon2.position.x +=ballon2.vitx ;
            ballon2.position.y +=ballon2.vity ;              
        }   
        if (((ballon1.position.x + ballon1.radius) >= GetScreenWidth()) || (ballon1.position.x <= 0)) ballon1.vitx *= -1;
        if (((ballon2.position.x + ballon2.radius) >= GetScreenWidth()) || (ballon2.position.x <= 0)) ballon2.vitx *= -1;
        if (((ballon1.position.y + ballon1.radius) >= GetScreenHeight()) || (ballon1.position.y <= 0)) ballon1.vity *= -1;
        if (((ballon2.position.y + ballon2.radius) >= GetScreenHeight()) || (ballon2.position.y <= 0)) ballon2.vity *= -1;
        
        if (check_coll_s_b(singe1, ballon1)){
            if (fleche1.cible==0){
                fleche1=check_coll_b_f(fleche1,ballon1,singe1);
            }
            if (fleche1.cible==1){
                ballon1.etat=0; 
                fleche1.etat=0; 
            }  
            if (fleche1.cible==2){
                fleche1.etat=0;
            }
        }  

        if (check_coll_s_b(singe1, ballon2)){
            if (fleche2.cible==0){
                fleche2=check_coll_b_f(fleche2,ballon2,singe1);
            }
            if (fleche2.cible==1){
                ballon2.etat=0; 
                fleche2.etat=0; 
            } 
            if (fleche2.cible==2){
                fleche2.etat=0;
            } 
        }  
        
        dessiner_singe(singe1); 
        dessiner_fleche(fleche1); 
        dessiner_fleche(fleche2); 
        dessiner_ballon(ballon1);
        dessiner_ballon(ballon2); 
        EndDrawing();
    }
    CloseWindow(); 
    return 0;
}