#include "utilities.h"
#include "properties.h"
#include "point.h"
#include <time.h>
#include <stdlib.h>

void setRandomPoints (struct Point points[], int pointNumber)
{
    // This function fills the pointLocation matrix with a random x and y position
    // line 0 - x position
    // line 1 - y position
    srand (time(0));

    for (int i = 1; i <= pointNumber; i++) {
    	points[i].x = rand() % WINWIDTH;
    	points[i].y = rand() % WINHEIGHT;
    }
}