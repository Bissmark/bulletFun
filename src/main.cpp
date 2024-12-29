#include <raylib.h>
#include "enemy.h"
#include "player.h"
#include "enemySpawner.h"
#include <raymath.h>
#include <cmath>

int main() 
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "2D Game");

    Player player;
    EnemySpawner enemySpawner(player, 5, 2);
    // Enemy enemy(player);

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
        player.Fire();
        enemySpawner.Update(deltaTime);

        camera.target = Vector2Lerp(camera.target, player.playerPosition, 0.1f);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(TextFormat("Health: %i", player.healthPoints), 10, 10, 20, RED);
            BeginMode2D(camera);
                enemySpawner.Draw();
                player.Draw();
            EndMode2D();    
        EndDrawing();
    }
    
    CloseWindow();
}