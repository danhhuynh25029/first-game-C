#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
bool checkCollision(int px,int py,int bx,int by){
    if(by + 64 > py && bx + 64 > px + 64 && px + 64 > bx){
        return true;
    }else if(by + 64 > py && bx + 64 > px && px + 64 > bx + 64){
        return true;
    }
    return false;
}
int main(void){
    int nb = 0;
    InitWindow(500,500,"first game");
    int p[] = {0,436,0};
    char s[1000];
    int b[5][2];
    for(int i = 0; i < 5; i++){
        b[i][0] = 0 + rand() % (449 + 1);
        b[i][1] = 0;
    }
    bool close = false;
    Texture2D img  = LoadTexture("assets/player.png");
    Texture2D brick = LoadTexture("assets/brick.png"); 
    SetTargetFPS(60);
    int frameCount = 0;
    while(!WindowShouldClose()){
        
        ClearBackground(WHITE);
        BeginDrawing();
            sprintf(s, "%d", p[2]);
            DrawText(s,0,0,20,BLACK);
            if(close == true){
                if(IsKeyDown(KEY_R)){
                    for(int i = 0 ; i < nb ; i++){
                        b[i][1] = 0;
                        b[i][0] = 0 + rand() % (449 + 1);
                    }
                    close = false;
                    nb = 0;
                    p[2] = 0;
                }
            }
            if(close == false){
                if(IsKeyDown(KEY_LEFT) && p[0] > 0)  p[0] -= 5;
                if(IsKeyDown(KEY_RIGHT) && p[0] + 64 < 500 ) p[0] += 5;
            }
            for(int i = 0 ; i <= nb; i++){
                close = checkCollision(p[0],p[1],b[i][0],b[i][1]) == true;
                if(b[i][1] > 500 && close == false){
                    b[i][1] = 0;
                    b[i][0] = 0 + rand() % (449 + 1);
                    
                }
                if(close == true){
                    DrawText("You Close,Press R to Restart",100,240,20,BLACK);
                    break;
                }else{
                    b[i][1] += 5;
                }
                DrawTexture(brick,b[i][0],b[i][1],WHITE); 
            }
            
            DrawTexture(img,p[0],p[1],WHITE);
            if(frameCount % 60 == 0 && close == false){
                if(nb < 4) {
                    nb += 1;
                    p[2] += 1;
                }
                else{
                    bool tmp = true;
                    for(int i = 0 ; i < nb ; i++){
                        if(b[i][1] < 500) tmp = false; 
                    }
                    if(tmp == true) nb = 0;
                }
            }
            frameCount += 1;
        EndDrawing();
        
    }
    CloseWindow();
    return 0;
}