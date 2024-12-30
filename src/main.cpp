#include <raylib.h>
#include "enemy.h"
#include "player.h"
#include "enemySpawner.h"
#include "background.h"
#include <raymath.h>
#include <cmath>
#include <iostream>

int main() 
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "2D Game");

    Player player;
    EnemySpawner enemySpawner(player, 5, 2);
    Background background;

    Camera2D camera = { 0 };
    camera.target = player.playerPosition;
    camera.offset = (Vector2){ screenWidth / 2, screenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        Vector2 previousPosition = player.playerPosition;

        player.Fire();
        player.Move();
        player.Update();
        enemySpawner.Update(deltaTime);

        Vector2 playerMovement = Vector2Subtract(player.playerPosition, previousPosition);
        background.Update(player.playerPosition);

        camera.target = Vector2Lerp(camera.target, player.playerPosition, 0.1f);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);
                background.Draw();
                enemySpawner.Draw();
                player.Draw();
            EndMode2D();    
            DrawText(TextFormat("Health: %i", player.healthPoints), 10, 10, 20, RED);
            DrawText(TextFormat("Player Position: (%.2f, %.2f)", player.playerPosition.x, player.playerPosition.y), 10, 30, 20, RED);
            DrawText(TextFormat("Player Movement: (%.2f, %.2f)", playerMovement.x, playerMovement.y), 10, 50, 20, RED);
        EndDrawing();
    }
    
    CloseWindow();
}