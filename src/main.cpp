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

    Player player;
    Enemy enemy(player);

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        player.Move();
        player.Update();
        enemy.Move();
        enemy.Update();

        BeginDrawing();
            ClearBackground(RAYWHITE);

            enemy.Draw();
            player.Draw();
        EndDrawing();
    }
    
    CloseWindow();
}