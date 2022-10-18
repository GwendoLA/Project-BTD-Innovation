
#include "raylib.h"
#include <iostream>
#include <vector>
 

void singe(Vector2 sp, Vector2 ss) {
   BeginDrawing(); 
   ClearBackground(RAYWHITE);
   DrawRectangleV(sp,ss,RED); 
   EndDrawing();
   
}

void autre(Vector2 sp,Vector2 ss){
   BeginDrawing();
   ClearBackground(RAYWHITE);
   DrawRectangleV(sp,ss,RED); 
   EndDrawing(); 
   }

void vide(){
   BeginDrawing();
   ClearBackground(RAYWHITE);
   EndDrawing(); 
}



int main(void){

   const int screenWidth = 800;
   const int screenHeight = 450;
   
   InitWindow(screenWidth, screenHeight, "test singe");      
   SetTargetFPS(60);
   int s_start=0 ;
   Vector2 s_p = {10,10};
   Vector2 s_s = {50,50};
   int i = 0;

   while (!WindowShouldClose()){
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ 
         s_start = (s_start+1)%3;
         
      }

      if (s_start==1){  
         Vector2 s_p = GetMousePosition();
         Vector2 s_s = { 50 , 50 }; 
         singe(s_p,s_s);
         s_start=1 ;
      }

      else if (s_start==2){
         static Vector2 s_p = GetMousePosition();
         static Vector2 s_s = { 50 , 50 }; 
         autre(s_p,s_s);
         s_start=2 ;
      }   

      else {
         vide();
         s_start=0; 
      }     
   }
   CloseWindow();    
   return 0;
}


