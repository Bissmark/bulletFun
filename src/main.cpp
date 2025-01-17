#include <raylib.h>
#include "enemy.h"
#include "player.h"
#include "enemySpawner.h"
#include "background.h"
#include "powerup.h"
#include "characterSelection.h"
#include "tilemap.h"
#include "skillPickup.h"
#include <raymath.h>
#include <cmath>
#include <iostream>

int main() 
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "2D Game");

    Player player;
    EnemySpawner enemySpawner(player, 2);
    Background background;
    Powerup powerup;
    CharacterSelection characterSelection(player);
    Tilemap tilemap(16, 32);
    SkillPickup skillPickup;

    SetTargetFPS(60);
    
    bool characterSelected = false;
    int currentLevel = 1;

    tilemap.Generate(currentLevel);
    player.playerPosition = tilemap.GetCenterPosition();
    
    Camera2D camera = { 0 };
    camera.target = player.playerPosition;
    camera.offset = (Vector2){ screenWidth / 2, screenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        if (!characterSelected) {
            characterSelection.Update();
            if (characterSelection.IsCharacterSelected()) {
                characterSelected = true;
                player.playerType = characterSelection.GetSelectedPlayerType();
            }
        } else {
            if (!player.gamePaused) {
                player.Move();
                player.Update();
                player.AutoAttack(enemySpawner.enemies, deltaTime);
                powerup.Update(player);
                skillPickup.Update(player);
                enemySpawner.Update(deltaTime);

                //background.Update(player.playerPosition);
            }

            camera.target = Vector2Lerp(camera.target, player.playerPosition, 0.1f);
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            if (!characterSelected) {
                characterSelection.Draw();
            } else {
                BeginMode2D(camera);
                    tilemap.Draw(player.playerPosition);
                    //background.Draw();
                    enemySpawner.Draw();
                    powerup.Draw();
                    skillPickup.Draw();
                    player.Draw();
                EndMode2D();
                player.DrawExp();
                player.DrawLevelUpBox();
                DrawText(TextFormat("Health: %i", player.healthPoints), 10, 10, 20, RED);
                DrawText(TextFormat("Elapsed Time: %i seconds", (int)player.elapsedTime), 10, 50, 20, RED);
                DrawText(TextFormat("%i", player.level), 30, screenHeight - 50, 30, WHITE);
            }
        EndDrawing();
    }
    
    CloseWindow();
}