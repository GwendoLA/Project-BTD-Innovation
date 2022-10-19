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
    Rectangle box1 = { 50, 50, 200, 200 };
    Rectangle box2 = { 250, 50, 200, 200 };
    Rectangle box3 = { 250, 250, 200, 200 };
    Rectangle box4 = { 50, 250, 200, 200 };

    // LISTE DES RECTANGLES QUI VONT ETRE PARCOURRUS PAR LE BALLON
    Rectangle liste_R[6]={box1,box2,box3,box4,box1,box2};

    /// (COL) int boxASpeedX = 2;
    /// (COL) int boxASpeedY = 3;
    bool pause = false;
    int i=0;

    Ballon ballon1= creer_ballon ({150,150}, 50, 5);
    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(box1, GREEN);
        DrawRectangleRec(box2, BLUE);    
        DrawRectangleRec(box3, PURPLE);
        DrawRectangleRec(box4, YELLOW);

        Vector4 bouge = bouger_ballon(ballon1,liste_R[2],liste_R[3]);
        
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;
        if (!pause) {
            /// (COL) boxA.x += boxASpeedX;
            /// (COL) boxA.y += boxASpeedY;   
            if (IsKeyPressed(KEY_T)){ 
                Vector4 bouge = bouger_ballon(ballon1,liste_R[i],liste_R[i+1]);
                if (ballon1.position.x!=bouge.z){
                    ballon1.position.x+=(bouge.x);   
                }
                if (ballon1.position.y!=bouge.w){
                    ballon1.position.y+=(bouge.y);
                }                
                if ((ballon1.position.x==bouge.z)&&(ballon1.position.y==bouge.w)){
                        i+=1;
                }
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