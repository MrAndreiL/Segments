#include "raylib.h"
#include "properties.h"
#include "utilities.h"
#include "point.h"
 
static void drawTitleScreen(void)
{
    // BackGround Rectangle for image.
    int backWidth = GetScreenWidth() / 3;
    int backHeight = GetScreenHeight() / 3;
    float roundness = 0.2f;
    int segments = 0;
    Rectangle backRect = {GetScreenWidth() / 2 - backWidth / 2, 
                          GetScreenHeight() / 2 - backHeight,
                           backWidth, backHeight};
    DrawRectangleRounded(backRect, roundness, segments, GRAY);
}

int main(void)
{
    InitWindow(WINWIDTH, WINHEIGHT, "Segmente");
    SetWindowMonitor (1);
    SetTargetFPS(60); 
    
    // Upload placeholder image.
    
    struct Point pointArray[10]; 
    setRandomPoints (pointArray, 10);          

    while (!WindowShouldClose())    
    {
        BeginDrawing();
            drawTitleScreen();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();        

    return 0;
}