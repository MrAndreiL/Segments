#include "game.h"
#include "raylib.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/*
    point[0] - X value
    point[1] - Y value
    pair - Which point is it associated with.
         -1 -> associated with the current position of the mouse.
         -2 -> is not associated.
    TODO(Andrei) - Add a player index in the struct.
*/

struct Segment
{
    int point[2]; 
	int pair;
};

static struct Segment segment[30];
static int length = 30; // TODO(Andrei) - Make the player choose based on levels.
static int radius = 8;
static float pointDis = 65.0f;

/* Functions regarding point spawning */

static int pointDistance (int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

static int isValidPoint (int index, int x, int y)
{
    if (!length)
        return 1;
    for (int i = 0; i < index; i++)
        if (pointDistance(x, y, segment[i].point[0], segment[i].point[1]) <= pointDis)
            return 0;
    return 1;
}   

static void setRandomPoints (Rectangle bound)
{
    const int lengthX = (int)(bound.x + bound.width);
    const int lengthY = (int)(bound.y + bound.height);
    
    srand(time(0));
    
    for (int i = 0; i < length; ) {
    	int x = rand() % lengthX;
        while (!(bound.x <= x && x <= bound.width))
             x = rand() % lengthX;
         
        int y = rand() % lengthY;
        while (!(bound.y <= y && y <= bound.height))
             y = rand() % lengthY;
         
        if (isValidPoint(i, x, y)) {
            segment[i].point[0] = x;
            segment[i].point[1] = y;
            segment[i].pair = -2;
            i++;
        }
    }
}

// Graphical rendering and pre-rendering functions

static void DrawBackground(Rectangle backRect, Rectangle frontRect)
{
    const float roundness = 0.2f;
    const int segments = 0;
    DrawRectangleRounded(backRect, roundness, segments, GRAY);
    DrawRectangleRounded(frontRect, roundness, segments, WHITE);
}

static void DrawPoints()
{
    for (int i = 0; i < length; i++)
        DrawCircle(segment[i].point[0], segment[i].point[1], radius, BLACK);
}

static void Render(Rectangle backRect, Rectangle frontRect)
{
    ClearBackground(WHITE);
    DrawBackground(backRect, frontRect);
    DrawPoints();
}

static void DelayTime(float seconds)
{
    seconds += GetTime();
    while(GetTime() < seconds) // Delay effect based on delta time
              ;
}

static void PreRender(Rectangle backRect, Rectangle frontRect)
{
    const float seconds = 0.35f;
    for (int i = 0; i < length;) {
        BeginDrawing();
            ClearBackground(WHITE);
            
            DrawBackground(backRect, frontRect);
            
            for (int j = 0; j < i; j++)
                DrawCircle(segment[j].point[0], segment[j].point[1], radius, BLACK);
        EndDrawing();
        
        DelayTime(seconds);
        i++;
    }
}

static void MouseAction()
{
    Vector2 mousePos = GetMousePosition();
    
    static int carry = 0; // if there are lines drawn to the mouse 
        
    for (int i = 0; i < length; i++) 
        if (pointDistance(mousePos.x, mousePos.y, segment[i].point[0], segment[i].point[1]) <= radius
                          && segment[i].pair < 0) 
        {
            DrawCircle(segment[i].point[0], segment[i].point[1], radius, MAROON);
            
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (carry) {
                    for (int j = 0; j < length; j++)
                        if (segment[j].pair == -1) {
                            segment[j].pair = i;
                            segment[i].pair = j;
                            carry = 0;
                            break;
                        }
                } else {
                    carry = 1;
                    segment[i].pair = -1;
                }
            }
        }
}   

static void DrawSegment()
{
    const float thickness = 6.0f;
    
    Vector2 mousePos = GetMousePosition();
    
    for (int i = 0; i < length; i++)
        if (segment[i].pair != -2) {
            Vector2 startPos = {segment[i].point[0], segment[i].point[1]};
        
            if (segment[i].pair == -1)
                DrawLineEx(startPos, mousePos, thickness, BLACK);
            else {
                Vector2 endPos = {segment[segment[i].pair].point[0], segment[segment[i].pair].point[1]};
                DrawLineEx(startPos, endPos, thickness, BLACK);
            }
        }
}

void startGame()
{
    // Background rectangle
    Rectangle backRect = { 60, 50, GetScreenWidth() - 120, (GetScreenHeight() - GetScreenHeight() / 4) - 50};
    Rectangle frontRect = { 70, 60, GetScreenWidth() - 140, (GetScreenHeight() - GetScreenHeight() / 4) - 70};
    Rectangle bound = {frontRect.x + 50, frontRect.y + 50, frontRect.width - 50, frontRect.height - 50};
    setRandomPoints(bound);
                                                                                        
    PreRender(backRect, frontRect);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
            Render(backRect, frontRect);
            MouseAction();
            DrawSegment();
        EndDrawing();
    }
    CloseWindow();
}
