#pragma once
#include "raylib.h"

/*
    point[0] - X value
    point[1] - Y value
    pair - Which point is it associated with.
         -1 -> not associated
*/
struct Segment
{
    Vector2 point;
	int pair;
    int valid;
};

struct Segment segment[30];

int pairedPoints[30];

extern int length; 

extern int nrSegments;

extern int gameState;

extern int radius;

extern float pointDis;

extern float thickness;

extern int carry;

int pointDistance (int x1, int y1, int x2, int y2);

void DelayTime(float seconds);

int orientation(Vector2 point1, Vector2 point2, Vector2 point3);

int Max(int x, int y);

int Min(int x, int y);

int onSegment(Vector2 point1, Vector2 point2, Vector2 point3);

int isValidSegment(Vector2 startPos, Vector2 mousePos, Vector2 segmentStart, Vector2 segmentEnd);