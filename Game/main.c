#include "raylib.h"
#include "properties.h"
#include "utilities.h"
#include "point.h"
 
static void drawTitleScreen(Rectangle backRect)
{
    // BackGround Rectangle for image.
    int backWidth = GetScreenWidth() / 3;
    int backHeight = GetScreenHeight() / 3;
    float roundness = 0.2f;
    int segments = 0;
    DrawRectangleRounded(backRect, roundness, segments, GRAY);
}

int main(void)
{
    //No sound
    //main.c:25:10: warning: variable 'btnAction' set but not used [-Wunused-but-set-variable]
    //main.c:24:9: warning: variable 'btnState' set but not used [-Wunused-but-set-variable]
    
    InitWindow(WINWIDTH, WINHEIGHT, "Segmente");

    SetWindowMonitor (1);
    SetTargetFPS(60); 
    
    // Upload placeholder image.
    Rectangle backRect = {GetScreenWidth() / 2 - backWidth / 2, 
                          GetScreenHeight() / 2 - backHeight,
                           backWidth, backHeight};
    Image titlePhoto = LoadImage ("Resources/titlephoto.png");
    ImageCrop (&titlePhoto, backRect);


    /* Buttons */
    InitAudioDevice();
    
    //Sound fxButton = LoadSound("Resources/");
    Texture2D button = LoadTexture("Resources/button.png");
    
    int frameHeight = button.height/NUM_FRAMES;
    Rectangle sourceRec = {0,0,button.width,frameHeight};
    
    Rectangle btnBounds = {WINWIDTH-button.width/2,WINHEIGHT-button.height/NUM_FRAMES/2,button.width,frameHeight};
    int btnState = 0;
    bool btnAction = false;
    Vector2 mousePoint = { 0.0f, 0.0f };
    
    struct Point pointArray[10]; 
    setRandomPoints (pointArray, 10);          

    while (!WindowShouldClose())    
    {
        mousePoint = GetMousePosition();
        btnAction = false;
        
        if(CheckCollisionPointRec(mousePoint, btnBounds))
        {
            if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                btnState = 2;
            else
                btnState = 1;
            if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                btnAction = true;
        }
        else
            btnState = 0;
        BeginDrawing();
            drawTitleScreen(backRect);
            ClearBackground(RAYWHITE);
            DrawTextureRec(button, sourceRec, (Vector2){btnBounds.x, btnBounds.y}, GREEN);
        EndDrawing();
    }
    UnloadTexture(button);
    CloseAudioDevice();
    CloseWindow();        

    return 0;
}