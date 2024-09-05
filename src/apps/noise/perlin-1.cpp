#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include <stdio.h>

#include "libs/utils.hpp"

#include <FastNoise/FastNoise.h>

#include <chrono>


int main()
{

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;


    // Initialization
    //------------------------- -------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Random Walker");

    SetTargetFPS(60);

    int pY = GetScreenHeight() / 2;
    int pX = GetScreenWidth() / 2;

    auto node = FastNoise::New<FastNoise::Simplex>();

    float noise[screenWidth * screenHeight];

    Color *pixels = (Color *)malloc(screenWidth * screenHeight * sizeof(Color));
    Texture2D texture;

    int xDiff = 0;
    int yDiff = 0;
    int zDiff = 0;
    bool textureLoaded = false;
    std::chrono::_V2::system_clock::time_point t1,t2;
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {   
        t1 = high_resolution_clock::now();
        node->GenUniformGrid3D(noise, xDiff, yDiff, zDiff, screenWidth, screenHeight, 1, 0.03f, 1337);
        t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        std::cout << "Noise Generation: " << ms_double.count() << "ms\n";

        zDiff += 1;
        for (size_t y = 0; y < screenHeight; y++)
        {
            for (size_t x = 0; x < screenWidth; x++)
            {
                auto noiseValue = noise[y * screenWidth + x];
                pixels[y * screenWidth + x] = (Color){(unsigned char)((noiseValue + 1) * (255/2)), (unsigned char)(std::abs(noiseValue) * 255), 0, 255};
            }
        }
        t1 = high_resolution_clock::now();

        if (textureLoaded)
        {
            UpdateTexture(texture, pixels);
        }
        else
        {
            texture = {
                .id = rlLoadTexture(pixels, screenWidth, screenHeight, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1),
                .width = screenWidth,
                .height = screenHeight,
                .mipmaps = 1,
                .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
            };

            textureLoaded = true;
        }

        BeginDrawing();
        DrawTextureRec(texture, (Rectangle){0, 0, (float)texture.width, (float)-texture.height}, (Vector2){0, 0}, WHITE);
        DrawFPS(10, 10);
        EndDrawing();

        t2 = high_resolution_clock::now();
        ms_double = t2 - t1;
        std::cout << "Drawing: " << ms_double.count() << "ms\n";

    }
    UnloadTexture(texture);
    CloseWindow();
    return 0;
}