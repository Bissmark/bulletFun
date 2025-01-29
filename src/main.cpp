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

    TmxMap* map = LoadTMX(tmx);

    Player player;
    EnemySpawner enemySpawner(player, 2);
    Background background;
    CharacterSelection characterSelection(player);
    SkillPickup skillPickup;
    LevelUp levelUp(player);
    SkillBar skillBar;
    Powerup powerup(LoadTexture("Spritesheet/powerup/Health.png"), 0.5f);
    TerrainCollision tileCollision;
    tileCollision.LoadMap(tmx);

    SetTargetFPS(60);
    
    bool characterSelected = false;
    int currentLevel = 1;
    
    Camera2D camera = { 0 };
    camera.target = player.playerPosition;
    camera.offset = { static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        // Update camera offset dynamically based on window size
        int screenWidth = GetScreenWidth(); // Get the current window width
        int screenHeight = GetScreenHeight(); // Get the current window height
        camera.offset = { static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f };

        if (!characterSelected) {
            characterSelection.Update();
            if (characterSelection.IsCharacterSelected()) {
                characterSelected = true;
                player.playerType = characterSelection.GetSelectedPlayerType();
            }
        } else {
            if (!player.gamePaused) {
                Vector2 oldPosition = player.playerPosition;

                for (auto& enemy : enemySpawner.enemies) {
                    Vector2 oldPositionEnemy = enemy->enemyPosition;
                    enemy->Update(deltaTime);
                    if (tileCollision.CheckCollision(enemy->GetBoundingBox())) {
                        enemy->enemyPosition = oldPositionEnemy;
                    }
                }
                player.Move();
                // Check for collision with terrain
                if (tileCollision.CheckCollision(player.GetBoundingBox())) {
                    player.playerPosition = oldPosition; // Revert to old position if collision detected
                }
                player.Update(enemySpawner.enemies, deltaTime);
                player.AutoAttack(enemySpawner.enemies, deltaTime);
                powerup.Update(player, tileCollision);
                //skillPickup.Update(player, skillBar);
                skillPickup.Update(player, skillBar, tileCollision);
                enemySpawner.Update(deltaTime);
                skillBar.Update(player, enemySpawner.enemies, deltaTime);

                // for (auto& enemy : enemySpawner.enemies) {
                //     enemy->Update(deltaTime, tileCollision);
                // }
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

        // Start ImGui frame
            rlImGuiBegin();

            // Create ImGui window
            ImGui::Begin("Debug Window");
            ImGui::Text("Player Health: %i", player.healthPoints);
            ImGui::Text("Elapsed Time: %i seconds", (int)player.elapsedTime);
            ImGui::Text("Player Level: %i", player.level);
            ImGui::Text("Crit Chance: %i", player.critChance);
            ImGui::Text("Crit Damage: %f", player.critDamage);
            ImGui::Text("Base Damage: %i", player.baseDamage);
            ImGui::Text("Map Layers:");
            for (uint32_t i = 0; i < map->layersLength; ++i) {
                ImGui::Text("Layer %d: %s", i, map->layers[i].name);
            }

            ImGui::End();

            // End ImGui frame
            rlImGuiEnd();
        EndDrawing();
    }
    
    UnloadTMX(map);
    rlImGuiShutdown();
    CloseWindow();
}