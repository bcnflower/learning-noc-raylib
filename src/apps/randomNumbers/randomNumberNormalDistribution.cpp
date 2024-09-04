#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include <iostream>
#include <random>

int main()
{
    // Initialization
    //------------------------- -------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Random Number - Normal Distribution");

    SetTargetFPS(30);

    int pY = screenHeight / 2;
    int pX = screenWidth / 2;

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(screenWidth / 2, 100);

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    BeginTextureMode(target);
    ClearBackground(RAYWHITE);
    EndTextureMode();

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        pX = distribution(generator);
        // pY = distribution(generator);
        // std::cout<<pX<<std::endl;
        BeginTextureMode(target);
        DrawCircle(pX,pY, 20, (Color){0, 0, 0, 10});
        EndTextureMode();

        BeginDrawing();
        // ClearBackground(RAYWHITE);
        DrawTextureRec(target.texture, (Rectangle) { 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2) { 0, 0 }, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}