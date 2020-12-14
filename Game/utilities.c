#include "utilities.h"
#include "raylib.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
 

void setRandomPoints (struct Point point[], int pointNumber, Rectangle bound)
{
    srand (time(0));

    const int lengthX = (int)(bound.x + bound.width);
    const int lengthY = (int)(bound.y + bound.height);
    int x, y;
    for (int i = 0; i < pointNumber; i++) {
    	x = rand() % lengthX;
        while (!(bound.x <= x && x <= bound.width))
             x = rand() % lengthX;
        y = rand() % lengthY;
        while (!(bound.y <= y && y <= bound.height))
             y = rand() % lengthY;
        point[i].x = x;
        point[i].y = y;
        point[i].paired = 0;
    }
}