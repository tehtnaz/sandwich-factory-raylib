#include "include/raylib.h"
#include <stdio.h>
#include "checkColliders.h"

int main(void){
    InitWindow(1920, 1080, "Test");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}