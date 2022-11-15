#include "raylib.h"
#include <iostream>
#include <stdlib.h> 

typedef struct Ballon
{ // Structure Ballon
    int etat;
    Vector2 position;
    int radius;
    int rect;
    Color color;
} Ballon;


Ballon creer_ballon(Vector2 position, int radius)
{ // Pour créer un objet Ballon
    Ballon ballon;
    ballon.etat = 1;
    ballon.position = position;
    ballon.radius = radius;
    ballon.rect = 1;
    ballon.color = RED;
    return ballon;
}

void dessiner_ballon (Ballon ballon) { // Pour dessiner un ballon, en fonction position rayon et couleur
    if (ballon.etat==1){
    DrawCircleV(ballon.position,ballon.radius,ballon.color);
    }
}

Vector4 bouger_ballon(Ballon ballon,Rectangle r1, Rectangle r2){ // Pour bouger le ballon d'un rectangle à un autre
    float x1=r1.x+(r1.width)/2;
    float y1=r1.y+(r1.height)/2;
    float x2=r2.x+(r2.width)/2;
    float y2=r2.y+(r2.height)/2;
    float diff_x= x2-x1;
    float diff_y= y2-y1;
    return {diff_x, diff_y,x2,y2};
}
Ballon mouv(Ballon B, Rectangle liste_R[8], int nbr_r, bool pause){
    int i=0;
    int j = B.rect; 
    if (i!=j && j<nbr_r){  // i et j permettent les itérations
        i=j-1;
        Vector4 bouge = bouger_ballon(B,liste_R[i],liste_R[i+1]);
        if (B.position.x!=bouge.z){
            B.position.x+=(bouge.x/50); 
        }
        if (B.position.y!=bouge.w){
            B.position.y+=(bouge.y/50);
        } 
        if ((B.position.x==bouge.z)&&(B.position.y==bouge.w)){
            j+=1;
            B.rect=j; 
        }
        return B;               
    }
    else {
        B.etat=0;
        return B;            // le ballon est à la fin du chemin -> fin du round
    }   
}


// int main(){
//     InitWindow(screenWidth, screenHeight, "test collision avec structure");
//     SetTargetFPS(60);
//     /// (COL) Rectangle boxA = { 10, GetScreenHeight()/2.0f - 50, 50, 50 };

//     // POUR L'EXEMPLE ON UTILISE 8 RECTANGLE DISPOSE SUR LA MAP
//     Rectangle box1 = { 50, 50, 150, 150 };
//     Rectangle box2 = { 200, 50, 150, 150 };
//     Rectangle box3 = { 350, 50, 150, 150 };
//     Rectangle box4 = { 500, 50, 150, 150 };
//     Rectangle box5 = { 700, 200, 150, 150 };
//     Rectangle box6 = { 700, 350, 150, 150 };
//     Rectangle box7 = { 350, 350, 150, 150 };
//     Rectangle box8 = { 200, 550, 150, 150 };

////   Ballon ballon1= creer_ballon ({125,125}, 30);
////   Ballon ballon2= creer_ballon ({125,125}, 20);
////   ballon2.color=GREEN; // changer la couleur du ballon2, pour qu'on puisse le differencier du ballon1

//     // LISTE DES RECTANGLES QUI VONT ETRE PARCOURRUS PAR LE BALLON
//     Rectangle liste_R[8]={box1,box2,box3,box4,box5,box6,box7,box8};

//     /// (COL) int boxASpeedX = 2;
//     /// (COL) int boxASpeedY = 3;

////   bool pause = false; // jeu en pause ou non, avec la barre espace
////   int nbr_rectangle = 8; // nombre de rectangle du chemin
    
//     while (!WindowShouldClose()){

//         BeginDrawing();
//         ClearBackground(RAYWHITE);

//         DrawRectangleRec(box1, BLUE);
//         DrawRectangleRec(box2, BLUE);    
//         DrawRectangleRec(box3, BLUE);
//         DrawRectangleRec(box4, BLUE);
//         DrawRectangleRec(box5, BLUE);
//         DrawRectangleRec(box6, BLUE);    
//         DrawRectangleRec(box7, BLUE);
//         DrawRectangleRec(box8, BLUE);
        
////       if (IsKeyPressed(KEY_SPACE)) pause = !pause;
////       if (!pause) {
////           ballon1 = mouv(ballon1,liste_R,nbr_rectangle,pause); 
////           ballon2 = mouv(ballon2,liste_R,nbr_rectangle,pause);                 
////       }   
        
////       dessiner_ballon(ballon1);
////       dessiner_ballon(ballon2);  
//         EndDrawing();
//     }
//     CloseWindow(); 
//     return 0;
// }




/// (COL) if (((boxA.x + boxA.width) >= GetScreenWidth()) || (boxA.x <= 0)) boxASpeedX *= -1;
/// (COL) if (((boxA.y + boxA.height) >= GetScreenHeight()) || (boxA.y <= 0)) boxASpeedY *= -1;

/// (COL) if (CheckCollisionCircleRec(ballon1.position,ballon1.radius,boxA)){
/// (COL)    ballon1.etat = 0;
/// (COL) }
/// (COL) else {
/// (COL)     ballon1.etat = 1;
/// (COL) }
/// (COL) DrawRectangleRec(boxA, GOLD);  

