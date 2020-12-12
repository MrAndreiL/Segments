#include "raylib.h"
#include "properties.h"
#include "utilities.h"
#include "point.h"
 
static void drawTitleScreen(void)
{
    // BackGround Rectangle for image.
    int backWidth = GetScreenWidth() / 3;
    int backHeight = GetScreenHeight() / 3;
    float roundness = 0.2f;
    int segments = 0;
    Rectangle backRect = {GetScreenWidth() / 2 - backWidth / 2, 
                          GetScreenHeight() / 2 - backHeight,
                           backWidth, backHeight};
    DrawRectangleRounded(backRect, roundness, segments, GRAY);
}

static void startScreen(void)
{
    InitWindow(WINWIDTH, WINHEIGHT, "Segmente");

    SetWindowMonitor (1);
    SetTargetFPS(60); 


    /* Buttons */
    InitAudioDevice();
    
    //Sound fxButton = LoadSound("Resources/");
    Texture2D button = LoadTexture("Resources/button.png");

    Texture2D button2 = LoadTexture("Resources/sound.png");
    Texture2D button3 = LoadTexture("Resources/settings.png");
    
    int frameHeight = button.height/NUM_FRAMES;
    int frameHeight2 = button2.height/NUM_FRAMES;
    int frameHeight3 = button3.height/NUM_FRAMES;
    
    Rectangle sourceRec = {0,0,button.width,frameHeight};
    Rectangle btnBounds = {WINWIDTH/0.825-button.width/2,WINHEIGHT/0.85-button.height/2,button.width,frameHeight};
    
    Rectangle sourceRec2 = {0,0,button2.width,frameHeight2};
    Rectangle btn2Bounds = {WINWIDTH/0.85-button2.width/2,WINHEIGHT/0.725-button2.height/2,button2.width,frameHeight2};
    
    Rectangle sourceRec3 = {0,0,button3.width,frameHeight3};
    Rectangle btn3Bounds = {WINWIDTH/0.785-button3.width/2,WINHEIGHT/0.725-button3.height/2,button3.width,frameHeight3};
    
    int btnState = 0;
    bool btnAction = false;
    Vector2 mousePoint = { 0.0f, 0.0f };
    

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
        sourceRec.y = btnState*frameHeight;
        //sourceRec.y = btnState*frameHeight2;
        if (btnAction) {
            UnloadTexture(button);
            UnloadTexture(button2);
            CloseAudioDevice();
            CloseWindow();
            return;
        }

        
        BeginDrawing();
            drawTitleScreen();
            ClearBackground(RAYWHITE);
            DrawTextureRec(button, sourceRec, (Vector2){btnBounds.x, btnBounds.y}, GREEN);
            
            DrawTextureRec(button, sourceRec, (Vector2){btnBounds.x, btnBounds.y}, RAYWHITE);
            DrawTextureRec(button2, sourceRec2, (Vector2){btn2Bounds.x, btn2Bounds.y}, RAYWHITE);
            DrawTextureRec(button3, sourceRec3, (Vector2){btn3Bounds.x, btn3Bounds.y}, RAYWHITE);
        EndDrawing();
    }
    
    //UnloadTexture(button);
    //UnloadTexture(button2);
    //CloseAudioDevice();
    //CloseWindow();
}

static void gameScreen(void)
{
    InitWindow(0, 0, "Segments");
    SetWindowMonitor(1);
    SetTargetFPS(60);
    
    // Linie
    int liniesx = 0;
    int liniesy = GetScreenHeight() - GetScreenHeight() / 4;
    int linienx = GetScreenWidth();
    int linieny = GetScreenHeight() - GetScreenHeight() / 4;
     
    Rectangle rec1 = { 60, 50, GetScreenWidth() - 120, liniesy - 50};
    Rectangle rec2 = { 70, 60, GetScreenWidth() - 140, liniesy - 70};
    
    struct Point points[10];
    setRandomPoints(points, 10, rec2.x, rec2.y, rec2.width, rec2.height);
    for (int i = 0; i < 10; i++)
                printf ("%d %d\n", points[i].x, points[i].y);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
            DrawRectangleRounded(rec1, 0.2f, 0, GRAY);
            DrawRectangleRounded(rec2, 0.2, 0, WHITE);
            ClearBackground(WHITE);
        EndDrawing();
    }
    CloseWindow();
}

int main(void)
{
    startScreen();
    gameScreen();
    return 0;
}