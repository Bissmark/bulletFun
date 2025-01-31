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
#include "rlimGui.h"
#include <raymath.h>
#include <cmath>
#include <iostream>
#include "imgui.h"
#include "inGameMenu.h"

//#define RAYTMX_IMPLEMENTATION
#include "raytmx.h"
#include "terrainCollisionDetection.h" 

int main() 
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    const char* tmx = "Tileset/level1.tmx";

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    InitWindow(screenWidth, screenHeight, "2D Game");

    rlImGuiSetup(true);
    SetExitKey(KEY_NULL);

    TmxMap* map = LoadTMX(tmx);

    Player player;
    TerrainCollision tileCollision;
    EnemySpawner enemySpawner(player, 2, tileCollision);
    Background background;
    CharacterSelection characterSelection(player);
    SkillPickup skillPickup;
    LevelUp levelUp(player);
    SkillBar skillBar;
    Powerup powerup(LoadTexture("Spritesheet/powerup/Health.png"), 0.5f);
    tileCollision.LoadMap(tmx);
    InGameMenu inGameMenu;

    SetTargetFPS(60);
    
    bool characterSelected = false;
    int currentLevel = 1;
    bool showPauseMenu = false;
    
    Camera2D camera = { 0 };
    camera.target = player.playerPosition;
    camera.offset = { static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        camera.offset = { static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f };

        if (IsKeyPressed(KEY_ESCAPE)) {
            showPauseMenu = !showPauseMenu;
            player.gamePaused = showPauseMenu;
        }

        if (!characterSelected) {
            characterSelection.Update();
            if (characterSelection.IsCharacterSelected()) {
                characterSelected = true;
                player.playerType = characterSelection.GetSelectedPlayerType();
            }
        } else {
            if (!player.gamePaused) {
                Vector2 oldPosition = player.playerPosition;

                player.Move();
                if (tileCollision.CheckCollision(player.GetBoundingBox())) {
                    player.playerPosition = oldPosition;
                }
                player.Update(enemySpawner.enemies, deltaTime);
                player.AutoAttack(enemySpawner.enemies, deltaTime);
                powerup.Update(player, tileCollision);
                skillPickup.Update(player, skillBar, tileCollision);
                enemySpawner.Update(deltaTime);
                skillBar.Update(player, enemySpawner.enemies, deltaTime);
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
                    tileCollision.Draw();
                    powerup.Draw();
                    skillPickup.Draw();
                    enemySpawner.Draw();
                    player.Draw(camera);
                EndMode2D();
                player.DrawExp();
                skillBar.Draw(player, camera);
                if (player.leveledUp && !player.leveledUpWindowActive) {
                    player.leveledUpWindowActive = true;
                    levelUp.currentUpgrades = levelUp.GetRandomUpgrades();
                }
                if (player.leveledUpWindowActive) {
                    levelUp.DrawLevelUpBox();
                }
                DrawText(TextFormat("Health: %i", player.healthPoints), 10, 10, 20, RED);
                DrawText(TextFormat("Elapsed Time: %i seconds", (int)player.elapsedTime), 10, 50, 20, RED);
                DrawText(TextFormat("%i", player.level), GetScreenWidth() - 27, GetScreenHeight() - 37, 40, WHITE);
            }

            if (showPauseMenu) {
                inGameMenu.Draw(player, showPauseMenu);
            }
        EndDrawing();
    }
    
    UnloadTMX(map);
    rlImGuiShutdown();
    CloseWindow();
}