#include <raylib.h>
#include "enemy.h"
#include "player.h"
#include "enemySpawner.h"
#include "background.h"
#include "powerup.h"
#include "characterSelection.h"
#include "tilemap.h"
#include "skillPickup.h"
#include "levelUp.h"
#include "skillBar.h"
#include <raymath.h>
#include <cmath>
#include <iostream>

#define RAYTMX_IMPLEMENTATION
#include "raytmx.h"

int main() 
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    const char* tmx = "Tileset/level1.tmx";

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    InitWindow(screenWidth, screenHeight, "2D Game");

    TmxMap* map = LoadTMX(tmx);

    Player player;
    EnemySpawner enemySpawner(player, 2);
    Background background;
    Powerup powerup;
    CharacterSelection characterSelection(player);
    Tilemap tilemap(16, 32);
    SkillPickup skillPickup;
    LevelUp levelUp(player);
    SkillBar skillBar;

    SetTargetFPS(60);
    
    bool characterSelected = false;
    int currentLevel = 1;

    tilemap.Generate(currentLevel);
    player.playerPosition = tilemap.GetCenterPosition();
    
    Camera2D camera = { 0 };
    camera.target = player.playerPosition;
    camera.offset = { static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2 };
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
                player.Update(enemySpawner.enemies, deltaTime);
                player.AutoAttack(enemySpawner.enemies, deltaTime);
                powerup.Update(player);
                skillPickup.Update(player, skillBar);
                enemySpawner.Update(deltaTime);
                skillBar.Update(player, enemySpawner.enemies, deltaTime);

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
                    DrawTMX(map, &camera, 0, 0, WHITE);
                    DrawTMXLayerTile(map, Rectangle({0, 0, 800, 600}), 0, 0, 0, WHITE);
                    //tilemap.Draw(player.playerPosition);
                    //background.Draw();
                    enemySpawner.Draw();
                    powerup.Draw();
                    skillPickup.Draw();
                    player.Draw(camera);
                EndMode2D();
                player.DrawExp();
                skillBar.Draw(player, camera);
                if (player.leveledUp) {
                    levelUp.DrawLevelUpBox();
                }
                DrawText(TextFormat("Health: %i", player.healthPoints), 10, 10, 20, RED);
                DrawText(TextFormat("Elapsed Time: %i seconds", (int)player.elapsedTime), 10, 50, 20, RED);
                DrawText(TextFormat("%i", player.level), GetScreenWidth() - 27, GetScreenHeight() - 37, 40, WHITE);
            }
        EndDrawing();
    }
    
    UnloadTMX(map);
    CloseWindow();
}