#include "raylib.h"
#include <iostream>
#include <stdlib.h> 

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
    int x1=r1.x+(r1.width)/2;
    int y1=r1.y+(r1.height)/2;
    float x2=r2.x+(r2.width)/2;
    float y2=r2.y+(r2.height)/2;
    float diff_x= x2-x1;
    float diff_y= y2-y1;
    return {diff_x, diff_y,x2,y2};
}

int main(){
    InitWindow(screenWidth, screenHeight, "test collision avec structure");
    SetTargetFPS(60);
    Rectangle boxA = { 10, GetScreenHeight()/2.0f - 50, 50, 50 };
    Rectangle box1 = { 50, 50, 200, 200 };
    Rectangle box2 = { 250, 50, 200, 200 };
    Rectangle box3 = { 250, 250, 200, 200 };
    Rectangle box4 = { 50, 250, 200, 200 };

    int boxASpeedX = 2;
    int boxASpeedY = 3;
    bool pause = false;

    Ballon ballon1= creer_ballon ({150,150}, 50, 5);
    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyPressed(KEY_SPACE)) pause = !pause;
        if (!pause) {
            // boxA.x += boxASpeedX;
            // boxA.y += boxASpeedY;   
            Vector4 bouge = bouger_ballon(ballon1,box1,box2);
            if (ballon1.position.x<bouge.z){
                ballon1.position.x+=(bouge.x/60);
            }
            if (ballon1.position.y<bouge.w){
                ballon1.position.y+=(bouge.y/60); 
            }
            if ((ballon1.position.x<bouge.z)&&(ballon1.position.y<bouge.w)){
                // le ballon est arrivé au deuxième rectangle, on peut passer à la translation suivante
            }
        }
        

        if (((boxA.x + boxA.width) >= GetScreenWidth()) || (boxA.x <= 0)) boxASpeedX *= -1;
        if (((boxA.y + boxA.height) >= GetScreenHeight()) || (boxA.y <= 0)) boxASpeedY *= -1;

    
        if (CheckCollisionCircleRec(ballon1.position,ballon1.radius,boxA)){
           ballon1.etat = 0;
        }
        else {
            ballon1.etat = 1;
        }
        
        // DrawRectangleRec(boxA, GOLD);  
        DrawRectangleRec(box1, GREEN);
        DrawRectangleRec(box2, BLUE);    
        DrawRectangleRec(box3, PURPLE);
        DrawRectangleRec(box4, YELLOW); 
        dessiner_ballon(ballon1);
        
        EndDrawing();
    }
    CloseWindow(); 
    return 0;
    }