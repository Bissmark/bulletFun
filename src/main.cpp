#include <raylib.h>
#include "enemy.h"
#include "player.h"
#include <raymath.h>
#include <cmath>

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

int main() 
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "2D Game");

    Player player;
    Enemy enemy(player);

    Camera2D camera = { 0 };
    camera.target = player.playerPosition;
    camera.offset = (Vector2){ screenWidth / 2, screenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        player.Move();
        player.Update();
        enemy.Move();
        enemy.Update();
        enemy.Attack(deltaTime);

        camera.target = Vector2Lerp(camera.target, player.playerPosition, 0.1f);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);
                enemy.Draw();
                player.Draw();
            EndMode2D();    
        EndDrawing();
    }
    
    CloseWindow();
}