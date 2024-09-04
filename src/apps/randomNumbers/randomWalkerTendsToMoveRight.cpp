#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "libs/utils.h"

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

    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        // DrawCircle(pX,pY,walkDistance,BLACK);
        DrawPixel(pX, pY, BLACK);
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

    CloseWindow();
    return 0;
}