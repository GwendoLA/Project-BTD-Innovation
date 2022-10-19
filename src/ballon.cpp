#include "raylib.h"
#include <iostream>
#include <stdlib.h> 

/////       INFOS         //////
//// LES LIGNES COMMENCANT PAR "/// (COL)" SONT CELLE CODANT UNE COLLISION ENTRE UN RECTANGLE EN MOUVEMENT ET UN CERLE///
//// LE CODE ACTIF PERMET DE FAIRE BOUGER UN BALLON ENTRE PLUSIEURS RECTANGLES /////

static int screenWidth = 800;
static int screenHeight = 600;

typedef struct Ballon { 
    int etat;
    Vector2 position;
    int radius;
    int vitesse;
    Color color; 
} Ballon;

Ballon creer_ballon (Vector2 position, int radius,int vitesse) {
    Ballon ballon;
    ballon.etat= 1;
    ballon.position= position;
    ballon.radius= radius;
    ballon.vitesse=vitesse;
    ballon.color= BLACK;
    return ballon;
}

void dessiner_ballon (Ballon ballon) {
    if (ballon.etat==1){
    DrawCircleV(ballon.position,ballon.radius,ballon.color);
    }
}

Vector4 bouger_ballon(Ballon ballon,Rectangle r1, Rectangle r2){
    float x1=r1.x+(r1.width)/2;
    float y1=r1.y+(r1.height)/2;
    float x2=r2.x+(r2.width)/2;
    float y2=r2.y+(r2.height)/2;
    float diff_x= x2-x1;
    float diff_y= y2-y1;
    return {diff_x, diff_y,x2,y2};
}

int main(){
    InitWindow(screenWidth, screenHeight, "test collision avec structure");
    SetTargetFPS(60);
    /// (COL) Rectangle boxA = { 10, GetScreenHeight()/2.0f - 50, 50, 50 };
    Rectangle box1 = { 50, 50, 150, 150 };
    Rectangle box2 = { 200, 50, 150, 150 };
    Rectangle box3 = { 350, 50, 150, 150 };
    Rectangle box4 = { 500, 50, 150, 150 };
    Rectangle box5 = { 500, 200, 150, 150 };
    Rectangle box6 = { 500, 350, 150, 150 };
    Rectangle box7 = { 350, 350, 150, 150 };
    Rectangle box8 = { 200, 350, 150, 150 };

    // LISTE DES RECTANGLES QUI VONT ETRE PARCOURRUS PAR LE BALLON
    Rectangle liste_R[8]={box1,box2,box3,box4,box5,box6,box7,box8};

    /// (COL) int boxASpeedX = 2;
    /// (COL) int boxASpeedY = 3;
    bool pause = false; // jeu en pause ou non, avec la barre espace
    int i=0;
    int j=1;
    int nbr_rectangle = 8; // nombre de rectangle du chemin

    Ballon ballon1= creer_ballon ({125,125}, 30, 5);
    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(box1, BLUE);
        DrawRectangleRec(box2, BLUE);    
        DrawRectangleRec(box3, BLUE);
        DrawRectangleRec(box4, BLUE);
        DrawRectangleRec(box5, BLUE);
        DrawRectangleRec(box6, BLUE);    
        DrawRectangleRec(box7, BLUE);
        DrawRectangleRec(box8, BLUE);
        
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;
        if (!pause) {
            /// (COL) boxA.x += boxASpeedX;
            /// (COL) boxA.y += boxASpeedY;   
            if (i!=j && j<nbr_rectangle){  // i et j permettent les itérations
                i=j-1;
                Vector4 bouge = bouger_ballon(ballon1,liste_R[i],liste_R[i+1]);
                if (ballon1.position.x!=bouge.z){
                    ballon1.position.x+=(bouge.x/60);   
                }
                if (ballon1.position.y!=bouge.w){
                    ballon1.position.y+=(bouge.y/60);
                }                
                if ((ballon1.position.x==bouge.z)&&(ballon1.position.y==bouge.w)){
                        j+=1;
                }
            }
            if (j==nbr_rectangle){
                // le ballon est à la fin du chemin -> fin du round
            }
        }
        

        /// (COL) if (((boxA.x + boxA.width) >= GetScreenWidth()) || (boxA.x <= 0)) boxASpeedX *= -1;
        /// (COL) if (((boxA.y + boxA.height) >= GetScreenHeight()) || (boxA.y <= 0)) boxASpeedY *= -1;

    
        /// (COL) if (CheckCollisionCircleRec(ballon1.position,ballon1.radius,boxA)){
        /// (COL)    ballon1.etat = 0;
        /// (COL) }
        /// (COL) else {
        /// (COL)     ballon1.etat = 1;
        /// (COL) }
        
        /// (COL) DrawRectangleRec(boxA, GOLD);  
         
        dessiner_ballon(ballon1);
        EndDrawing();
    }
    CloseWindow(); 
    return 0;
    }