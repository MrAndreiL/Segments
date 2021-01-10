#include "utilities.h"
#include <math.h>

int pointDistance (int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

void DelayTime(float seconds)
{
    seconds += GetTime();
    while(GetTime() < seconds) // Delay effect based on delta time
              ;
}

int orientation(Vector2 point1, Vector2 point2, Vector2 point3)
{
    int val = (point2.y - point1.y) * (point3.x - point2.x) -
              (point3.y - point2.y) * (point2.x - point1.x);
    
    if (val == 0) return 0; // colinear
    
    return (val > 0) ? 1 : 2; // clockwise or counterclockwise
}

int Max(int x, int y)
{
    return x > y ? x : y;
}

int Min(int x, int y)
{
    return x < y ? x : y;
}

int onSegment(Vector2 point1, Vector2 point2, Vector2 point3)
{
    // Check whether point2 resides inside point1-point3 segment.
    if (point2.x <= Max(point1.x, point3.x) && point2.x >= Min(point1.x, point3.x) &&
        point2.y <= Max(point1.y, point3.y) && point2.y >= Min(point1.y, point3.y))
        return 1;
        
    return 0;
}

int isValidSegment(Vector2 startPos, Vector2 mousePos, Vector2 segmentStart, Vector2 segmentEnd)
{
    // Find the four orientations needed for general and special cases.
    int o1 = orientation(startPos, mousePos, segmentStart);
    int o2 = orientation(startPos, mousePos, segmentEnd);
    int o3 = orientation(segmentStart, segmentEnd, startPos);
    int o4 = orientation(segmentStart, segmentEnd, mousePos);
    
    // General
    if (o1 != o2 && o3 != o4) return 0;
    
    // Special cases when the points are colinear.
    if (o1 == 0 && onSegment(startPos, mousePos, segmentStart)) return 0;
    
    if (o2 == 0 && onSegment(startPos, mousePos, segmentEnd)) return 0;
    
    if (o3 == 0 && onSegment(segmentStart, segmentEnd, startPos)) return 0;
    
    if (o4 == 0 && onSegment(segmentStart, segmentEnd, mousePos)) return 0;
    
    return 1;
}


