#include "raylib.h"
#include "properties.h"
#include "utilities.h"
#include "point.h"
#include <stdio.h>

int main(void)
{
    InitWindow(WINWIDTH, WINHEIGHT, "Segmente");
    SetWindowMonitor (1);
    SetTargetFPS(60); 
    
    struct Point pointArray[10]; 
    setRandomPoints (pointArray, 10);          

    while (!WindowShouldClose())    
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            for (int i = 1; i <= 10; i++) 
                DrawCircle (pointArray[i].x, pointArray[i].y, 5, BLACK);
        EndDrawing();
    }
    CloseWindow();        

    return 0;
}