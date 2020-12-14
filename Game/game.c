#include "game.h"
#include "raylib.h"
#include "utilities.h"

void startGame()
{
    //InitWindow(0, 0, "Segments");
    //SetWindowMonitor(1);
    //SetTargetFPS(60);
    
    // Linie
    int liniesx = 0;
    int liniesy = GetScreenHeight() - GetScreenHeight() / 4;
    int linienx = GetScreenWidth();
    int linieny = GetScreenHeight() - GetScreenHeight() / 4;
     
    Rectangle rec1 = { 60, 50, GetScreenWidth() - 120, liniesy - 50};
    Rectangle rec2 = { 70, 60, GetScreenWidth() - 140, liniesy - 70};
    
    struct Point point[51];
    Rectangle bound = {rec2.x + 50, rec2.y + 50, rec2.width - 50, rec2.height - 50};
    setRandomPoints(point, 50, bound);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
            DrawRectangleRounded(rec1, 0.2f, 0, GRAY);
            DrawRectangleRounded(rec2, 0.2, 0, WHITE);
            for (int i = 0; i < 50; i++)
                DrawCircle(point[i].x, point[i].y, 8, BLACK);
            ClearBackground(WHITE);
        EndDrawing();
    }
    CloseWindow();
}
