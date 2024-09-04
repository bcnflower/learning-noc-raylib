#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include <random>

int main()
{
    // Initialization
    //------------------------- -------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Random Number - Normal Distribution");

    SetTargetFPS(30);

    int pY = GetScreenHeight() / 2;
    int pX = GetScreenWidth() / 2;

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0, (GetScreenWidth() / 2) - 50);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        pX = distribution(generator);
        BeginDrawing();
        DrawCircle(pX, pY, 20, (Color){ 0, 0, 0, 10 });
        EndDrawing();
    }

    CloseWindow();
    return 0;
}