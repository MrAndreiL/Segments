#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    int PointsX[10];
    int PointsY[10];
    
    srand (time(0));
    
    for (int i = 1; i <= 10; i++) {
        int x = rand() % screenWidth;
        int y = rand() % screenHeight;
        PointsX[i] = x;
        PointsY[i] = y;
    }

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

            for (int i = 0; i <= 10; i++) 
                DrawCircle (PointsX[i], PointsY[i], 5, BLACK);
            
            //DrawCircleV(ballPosition, 50, RED);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}