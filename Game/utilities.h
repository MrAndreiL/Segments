#pragma once 
#include "raylib.h"

struct Point
{
	int x;
	int y;
	int paired;
};

void setRandomPoints(struct Point point[], int pointNumber, Rectangle bound);


