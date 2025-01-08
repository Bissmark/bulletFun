#include <raylib.h>
#include "enemy.h"
#include "player.h"
#include "enemySpawner.h"
#include "background.h"
#include "powerup.h"
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
    Powerup powerup;

    Camera2D camera = { 0 };
    camera.target = player.playerPosition;
    camera.offset = (Vector2){ screenWidth / 2, screenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        if (!player.gamePaused) {
            //player.Fire(camera);
            player.Move();
            player.Update();
            player.AutoAttack(enemySpawner.enemies, deltaTime);
            powerup.Update(player);
            enemySpawner.Update(deltaTime);

            background.Update(player.playerPosition);
        }

        camera.target = Vector2Lerp(camera.target, player.playerPosition, 0.1f);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);
                background.Draw();
                enemySpawner.Draw();
                powerup.Draw();
                player.Draw();
            EndMode2D();    
                player.DrawExp();
                player.DrawLevelUpBox();
            DrawText(TextFormat("Health: %i", player.healthPoints), 10, 10, 20, RED);
            DrawText(TextFormat("Elapsed Time: %i seconds", (int)player.elapsedTime), 10, 50, 20, RED);
            //DrawText(TextFormat("Player Position: (%.2f, %.2f)", player.playerPosition.x, player.playerPosition.y), 10, 30, 20, RED);
            //DrawText(TextFormat("Experience: %i", player.experiencePoints), 10, 70, 20, RED);
            DrawText(TextFormat("%i", player.level), 30, screenHeight - 50, 30, WHITE);
        EndDrawing();
    }
    
    CloseWindow();
}