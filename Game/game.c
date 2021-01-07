#include "game.h"
#include "raylib.h"
#include "utilities.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int length = 11;

int radius = 8;

float pointDis = 65.0f;

float thickness = 6.0f;

static int carry = -1; // If there is a segment currently carried by the mouse.

static int nrSegments = 0;

static int nrSegmentsLeft = 0;

static int pairedPoints[10];

static int gameState = 1; // 1 - player's turn, 0 - computer's turn

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

static void DrawInfo(Texture2D ExitSTexture, Texture2D ExitHTexture)
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    
    // Exit button.
    if (screenW - 50 <= mouseX && mouseX <= screenW && 0 <= mouseY && mouseY <= 50) {
        DrawTexture(ExitHTexture, screenW - 50, 0, RAYWHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            CloseWindow();
    }
    else DrawTexture(ExitSTexture, screenW - 50, 0, RAYWHITE);
    
    // Label with segment information.
    char text[100] = "Segments Left: ";
    char result[10];
    sprintf(result, "%d", nrSegmentsLeft);
    strcat(text, result);
    int TextX = screenW / 2 - 150;
    int TextY = (screenH - screenH / 4) + 50;
    DrawText(text, TextX, TextY, 25, BLACK);
    
    // Change Turn button.
    if (gameState) {
        int buttonX = TextX + 15;
        int buttonY = TextY + 50;
        int buttonW = 200;
        int buttonH = 75;
        
        if (buttonX <= mouseX && mouseX <= buttonX + buttonW &&
            buttonY <= mouseY && mouseY <= buttonY + buttonH) {
            DrawRectangle(buttonX, buttonY, buttonW, buttonH, GRAY);
            
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                gameState = 0;
        } 
        else DrawRectangle(buttonX, buttonY, buttonW, buttonH, BLACK);
    }
}

static void Render(Rectangle backRect, Rectangle frontRect)
{
    ClearBackground(WHITE);
    DrawFPS(0, 0);
    DrawBackground(backRect, frontRect);
    DrawPoints();
}

static void SegmentsLeft()
{
    // Returns the number of valid segments left.
    if (!nrSegments) {
        nrSegmentsLeft = (length * (length - 1) / 2);
        return;
    }
    
    int count = 0;
    for (int i = 0; i < length - 1; i++)
        for (int j = i + 1; j < length; j++)
            if (segment[i].pair == -1 && segment[j].pair == -1) {
                int value = 1;
                for (int k = 0; k < nrSegments; k++)
                    if (!isValidSegment(segment[i].point, segment[j].point, segment[pairedPoints[k]].point, segment[segment[pairedPoints[k]].pair].point)) {
                        value = 0;
                        break;
                    }
                if (value)
                    count++;
            }
             
    nrSegmentsLeft = count;
}

static void PreRender(Rectangle backRect, Rectangle frontRect)
{
    const float seconds = 0.20f;
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
    SegmentsLeft();
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
                    pairedPoints[nrSegments] = i;
                    nrSegments++;  
                    SegmentsLeft();
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
    /* Import necessary info */
    
    // Exit button.
    Image ExitS = LoadImage("Resources/ExitSimple.png");
    ImageResize(&ExitS, 50, 50);
    Texture2D ExitSTexture = LoadTextureFromImage(ExitS); 
    UnloadImage(ExitS);
    
    Image ExitH = LoadImage("Resources/ExitHover.png");
    ImageResize(&ExitH, 50, 50);
    Texture2D ExitHTexture = LoadTextureFromImage(ExitH); 
    UnloadImage(ExitH);
    
    
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
            DrawInfo(ExitSTexture, ExitHTexture);
            MouseAction();
            DrawSegment();
        EndDrawing();
    }
    
    UnloadTexture(ExitSTexture);
    UnloadTexture(ExitHTexture);
    CloseWindow();
}
