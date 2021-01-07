#include "player.h"
#include "raylib.h"

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
                }  
                break;                
            }
        }
        
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            carry = -1;
    }
}

void PlayerTurn()
{
    MouseAction();
}