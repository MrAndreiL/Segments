#include "utilities.h"
#include "properties.h"
#include "point.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void setRandomPoints (struct Point points[], int pointNumber, int x, int y, int width, int height)
{
    // This function fills the pointLocation matrix with a random x and y position
    // line 0 - x position
    // line 1 - y position
    srand (time(0));
    
    int widthBound  = x + width - 10;
    int heightBound = y + height - 10;

    for (int i = 1; i <= pointNumber; i++) {
    	points[i].x = (rand() % widthBound) + 10;
    	points[i].y = (rand() % heightBound) + 10;

    }
}