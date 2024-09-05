#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "libs/utils.hpp"

int main()
{
    // Initialization
    //------------------------- -------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Random Walker - Tends To Move Right");

    SetTargetFPS(60);

    int pY = GetScreenHeight() / 2;
    int pX = 10;
    // int walkDistance = 2;

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    BeginTextureMode(target);
    ClearBackground(RAYWHITE);
    EndTextureMode();

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginTextureMode(target);
        // DrawCircle(pX,pY,walkDistance,BLACK);
        DrawPixel(pX, pY, BLACK);
        EndTextureMode();

        BeginDrawing();
        DrawTextureRec(target.texture, (Rectangle){0, 0, (float)target.texture.width, (float)-target.texture.height}, (Vector2){0, 0}, WHITE);
        EndDrawing();

        const double random = rand_0_1();
        if (random < 0.4)
        { // A 40% chance of moving to the right
            pX++;
        }
        else if (random < 0.6)
        {
            pX--;
        }
        else if (random < 0.8)
        {
            pY++;
        }
        else
        {
            pY--;
        }
    }
    UnloadRenderTexture(target);
    CloseWindow();
    return 0;
}