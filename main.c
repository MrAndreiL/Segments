#include "raylib.h"
#include "properties.h"
#include "utilities.h"
#include "point.h"
#include <stdio.h>

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(WINWIDTH, WINHEIGHT, "Segmente");
    
    struct Point pointArray[10]; // an array that keeps track of where the points are in plane
    
    setRandomPoints (pointArray, 10);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            for (int i = 1; i <= 10; i++) 
                DrawCircle (pointArray[i].x, pointArray[i].y, 5, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}