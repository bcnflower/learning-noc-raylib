#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include <stdio.h>

#include "libs/utils.hpp"

int main()
{
    // Initialization
    //------------------------- -------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Random Walker");

    SetTargetFPS(60);

    int pY = GetScreenHeight() / 2;
    int pX = GetScreenWidth() / 2;
    int walkDistance = 2;

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    BeginTextureMode(target);
    ClearBackground(RAYWHITE);
    EndTextureMode();

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginTextureMode(target);
        DrawCircle(pX, pY, walkDistance, BLACK);
        EndTextureMode();

        pX += irandfrom(-walkDistance, walkDistance);
        pY += irandfrom(-walkDistance, walkDistance);

        BeginDrawing();
        DrawTextureRec(target.texture, (Rectangle) { 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2) { 0, 0 }, WHITE);
        EndDrawing();
    }
    UnloadRenderTexture(target);
    CloseWindow();
    return 0;
}