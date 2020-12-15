#include "game.h"
#include "raylib.h"
#include "utilities.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

static void setRandomPoints (struct Point point[], int pointNumber, Rectangle bound)
{
    const int lengthX = (int)(bound.x + bound.width);
    const int lengthY = (int)(bound.y + bound.height);
    srand(time(0));
    for (int i = 0; i < pointNumber; i++) {
    	int x = rand() % lengthX;
        while (!(bound.x <= x && x <= bound.width))
             x = rand() % lengthX;
        int y = rand() % lengthY;
        while (!(bound.y <= y && y <= bound.height))
             y = rand() % lengthY;
        point[i].x = x;
        point[i].y = y;
        point[i].paired = 0;
    }
}

static void DrawBackground(Rectangle backRect, Rectangle frontRect)
{
    const float roundness = 0.2f;
    const int segments = 0;
    DrawRectangleRounded(backRect, roundness, segments, GRAY);
    DrawRectangleRounded(frontRect, roundness, segments, WHITE);
}


static void DrawPoints(struct Point point[], int length)
{
    const int radius = 8;
    for (int i = 0; i < length; i++) 
        DrawCircle(point[i].x, point[i].y, radius, BLACK);
}

void startGame()
{
    // Background rectangle
    Rectangle backRect = { 60, 50, GetScreenWidth() - 120, (GetScreenHeight() - GetScreenHeight() / 4) - 50};
    Rectangle frontRect = { 70, 60, GetScreenWidth() - 140, (GetScreenHeight() - GetScreenHeight() / 4) - 70};
    
    // Random point spawning
    struct Point point[51];
    Rectangle bound = {frontRect.x + 50, frontRect.y + 50, frontRect.width - 50, frontRect.height - 50};
    setRandomPoints(point, 50, bound);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawBackground(backRect, frontRect);
            DrawPoints(point, 50);
        EndDrawing();
    }
    CloseWindow();
}
