#include "game.h"
#include "raylib.h"
#include "utilities.h"

static void setRandomPoints (struct Point point[], int pointNumber, Rectangle bound)
{
    const int lengthX = (int)(bound.x + bound.width);
    const int lengthY = (int)(bound.y + bound.height);
    srand (time(0));
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

void startGame()
{
    Rectangle rec1 = { 60, 50, GetScreenWidth() - 120, (GetScreenHeight() - GetScreenHeight() / 4) - 50};
    Rectangle rec2 = { 70, 60, GetScreenWidth() - 140, (GetScreenHeight() - GetScreenHeight() / 4) - 70};
    
    struct Point point[51];
    Rectangle bound = {rec2.x + 50, rec2.y + 50, rec2.width - 50, rec2.height - 50};
    setRandomPoints(point, 50, bound);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
            DrawRectangleRounded(rec1, 0.2f, 0, GRAY);
            DrawRectangleRounded(rec2, 0.2f, 0, WHITE);
            for (int i = 0; i < 50; i++)
                DrawCircle(point[i].x, point[i].y, 8, BLACK);
            ClearBackground(WHITE);
        EndDrawing();
    }
    CloseWindow();
}
