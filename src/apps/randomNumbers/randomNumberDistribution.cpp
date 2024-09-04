#include "raylib.h"

#include "rlgl.h"
#include "raymath.h"

#include "libs/utils.h"

// #include "FastNoise/FastNoise.h"

#define NO_OF_BARS 20

int main()
{
    // Initialization
    //------------------------- -------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Random Number distribution");

    SetTargetFPS(160);

    // int screenHeight = GetScreenHeight();
    // int screenWidth = GetScreenWidth();

    int randomCounts[NO_OF_BARS];
    int barWidth = screenWidth / NO_OF_BARS;
    for (int i = 0; i < NO_OF_BARS; i++)
    {
        randomCounts[i] = 0;
    }

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        int index = irandfrom(0, NO_OF_BARS);
        randomCounts[index]++;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int x = 0; x < NO_OF_BARS; x++)
        {
            DrawRectangle(x * barWidth, screenHeight - randomCounts[x], barWidth - 1, randomCounts[x],GRAY);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}