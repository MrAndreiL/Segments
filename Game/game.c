#include "game.h"
#include "raylib.h"
#include "utilities.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

int length = 30;

int radius = 8;

float pointDis = 65.0f;

float thickness = 6.0f;

static int carry = -1; // If there is a segment currently carried by the mouse.

/* Functions regarding point spawning */

static int isValidPoint (int index, int x, int y)
{
    if (!length)
        return 1;
    for (int i = 0; i < index; i++)
        if (pointDistance(x, y, segment[i].point.x, segment[i].point.y) <= pointDis)
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
            segment[i].point.x = x;
            segment[i].point.y = y;
            segment[i].pair = -1;
            segment[i].valid = 1;
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
        DrawCircle(segment[i].point.x, segment[i].point.y, radius, BLACK);
}

static void Render(Rectangle backRect, Rectangle frontRect)
{
    ClearBackground(WHITE);
    DrawBackground(backRect, frontRect);
    DrawPoints();
}

static void PreRender(Rectangle backRect, Rectangle frontRect)
{
    const float seconds = 0.15f;
    for (int i = 0; i < length;) {
        BeginDrawing();
            ClearBackground(WHITE);
            
            DrawBackground(backRect, frontRect);
            
            for (int j = 0; j < i; j++)
                DrawCircle(segment[j].point.x, segment[j].point.y, radius, BLACK);
        EndDrawing();
        
        DelayTime(seconds);
        i++;
    }
}

static void MouseAction()
{
    Vector2 mousePos = GetMousePosition();
        
    for (int i = 0; i < length; i++) {
        if (pointDistance(mousePos.x, mousePos.y, segment[i].point.x, segment[i].point.y) <= radius &&
                          segment[i].pair < 0) 
        {
            if (carry != i)
                DrawCircle(segment[i].point.x, segment[i].point.y, radius, MAROON);
            
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (carry == -1) 
                    carry = i;
                if (carry != i && segment[carry].valid) {
                    segment[carry].pair = i;
                    segment[i].pair = carry;
                    carry = -1;
                }  
                break;                
            }
        }
        
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            carry = -1;
    }
}   

static void DrawSegment()
{   
    for (int i = 0; i < length; i++) {
        Vector2 startPos = segment[i].point;
        
        if (segment[i].pair > 0) {
            Vector2 endPos = segment[segment[i].pair].point;
            DrawLineEx(startPos, endPos, thickness, BLACK);
        }
        
        if (carry == i) {
            Vector2 mousePos = GetMousePosition();
            
            segment[i].valid = 1;
            for (int j = 0; j < length && segment[i].valid; j++)
                if (segment[j].pair > 0 && segment[j].pair > j)
                    segment[i].valid = isValidSegment(startPos, mousePos, segment[j].point, segment[segment[j].pair].point);
            
            if (segment[i].valid)
                DrawLineEx(startPos, mousePos, thickness, BLACK);
            else
                DrawLineEx(startPos, mousePos, thickness, RED);
        }
    }
}

void startGame()
{
    length = 30;
    radius = 8;
    pointDis = 65.0f;
    thickness = 6.0f;
    
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
