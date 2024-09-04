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

    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        DrawCircle(pX, pY, walkDistance, BLACK);
        EndDrawing();

        pX += irandfrom(-walkDistance, walkDistance);
        pY += irandfrom(-walkDistance, walkDistance);
    }

    CloseWindow();
    return 0;
}