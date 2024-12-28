#include <raylib.h>
#include "enemy.h"
#include "player.h"

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

int main() 
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "2D Game");

    Enemy enemy;
    Player player;

    int currentFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 8;

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        player.Move();
        enemy.Update();
        
        // ++framesCounter;

        // if (framesCounter >= (60 / framesSpeed)) {
        //     framesCounter = 0;
        //     currentFrame++;

        //     if (currentFrame > 5) currentFrame = 0;

        //     //frameRec.x = (float)currentFrame * (float)playerIdle.width / 6;
        // }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            enemy.Draw();
            player.Draw();
            //DrawTextureRec(playerIdle, frameRec, playerPosition, WHITE);  // Draw part of the texture
        EndDrawing();
    }
    
    CloseWindow();
}