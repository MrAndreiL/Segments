#include "start.h"
#include "raylib.h"
#include "game.h"

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

void startScreen(void)
{
    InitWindow(0, 0, "Segmente");
    //InitAudioDevice();

    int backWidth = GetScreenWidth() / 3;
    int backHeight = GetScreenHeight() / 3;

    SetWindowMonitor(1);
    SetTargetFPS(60); 
    SetMousePosition(0, 0);
    
    const int WINWIDTH = GetScreenWidth()/3;
    const int WINHEIGHT = GetScreenHeight()/3;
    const int NUM_FRAMES = 1;

    int scenePath = 0; // All possible scene changes based on their path
    /*
        0 - current scene
        1 - game scene
    */

    /* Buttons */
    InitAudioDevice();
    
    Image Start = LoadImage("Resources/StartImage.png");
    Texture2D texture = LoadTextureFromImage(Start);
    UnloadImage(Start);
    //Sound fxButton = LoadSound("Resources/");
    Texture2D button = LoadTexture("Resources/StartButtonSimple.png");
    Texture2D button3 = LoadTexture("Resources/StartButtonHover.png");
    Texture2D button2 = LoadTexture("Resources/ExitSimple.png");
    Texture2D button4 = LoadTexture("Resources/ExitHover.png");
    
    int frameHeight = button.height/NUM_FRAMES;
    int frameHeight2 = button2.height/NUM_FRAMES;
    int frameHeight3 = button3.height/NUM_FRAMES;
    int frameHeight4 = button2.height/NUM_FRAMES;

    Rectangle sourceRec = {0,0,button.width,frameHeight};
    Rectangle btnBounds = {WINWIDTH/0.66-button.width/2,WINHEIGHT/0.5-button.height/2,button.width,frameHeight};
    
    Rectangle sourceRec3 = {0,0,button3.width,frameHeight3};
    Rectangle btn3Bounds = {WINWIDTH/0.66-button3.width/2,WINHEIGHT/0.5-button3.height/2,button3.width,frameHeight3};
    
    Rectangle sourceRec2 = {0,0,button2.width,frameHeight2};
    Rectangle btn2Bounds = {WINWIDTH/0.375-button2.width/2,WINHEIGHT/1.75-button2.height/2,button2.width,frameHeight2};
    
    Rectangle sourceRec4 = {0,0,button4.width,frameHeight4};
    Rectangle btn4Bounds = {WINWIDTH/0.375-button4.width/2,WINHEIGHT/1.75-button3.height/2,button4.width,frameHeight4};
    
    int btnState = 0;
    bool btnAction = false;
    Vector2 mousePoint = { 0.0f, 0.0f };
    Texture2D aux = LoadTexture("Resources/StartButtonSimple.png");
    Texture2D aux2 = LoadTexture("Resources/ExitSimple.png");

    while (!WindowShouldClose())
    {
        mousePoint = GetMousePosition();
        btnAction = false;
        if(CheckCollisionPointRec(mousePoint, btnBounds))
        {
            button=button3;
            if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                btnState = 2;
            else
                btnState = 1;
            if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                btnAction = true;
        }
        else
        {
            btnState = 0;    
            button = aux;
        }
        if(CheckCollisionPointRec(mousePoint, btn2Bounds))
        {
            button2=button4;
            if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                btnState = 2;
            else
                btnState = 1;
            if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                btnAction = true;
        }
        else
        {
            btnState = 0;    
            button2 = aux2;
        }
        sourceRec.y = btnState*frameHeight;
        if (btnAction) {
            scenePath = 1;
            break;
        }
        
        BeginDrawing();
            drawTitleScreen();
            ClearBackground(RAYWHITE);
            DrawTexture(texture, backWidth - texture.width/2 + 320, backHeight - texture.height/2, WHITE);
            DrawTextureRec(button, sourceRec, (Vector2){btnBounds.x, btnBounds.y}, RAYWHITE);
            DrawTextureRec(button2, sourceRec2, (Vector2){btn2Bounds.x, btn2Bounds.y}, RAYWHITE);
        EndDrawing();
    }
    
    UnloadTexture(button);
    UnloadTexture(button2);
    CloseAudioDevice();
    CloseWindow();
    if (scenePath == 1) // TODO (Andrei): improve this with a switch statement.
        startGame();
        
}
