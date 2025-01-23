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
#include "include/rlImGui.h"
#include <raymath.h>
#include <cmath>
#include <iostream>
#include "include/imgui.h"

#define RAYTMX_IMPLEMENTATION
#include "include/raytmx.h"
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
    Powerup powerup;
    CharacterSelection characterSelection(player);
    Tilemap tilemap(16, 32);
    SkillPickup skillPickup;
    LevelUp levelUp(player);
    SkillBar skillBar;
    TerrainCollision tileCollision;
    tileCollision.LoadMap(tmx);

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
                Vector2 oldPosition = player.playerPosition;
                player.Move();
                // Check for collision with terrain
                player.Update(enemySpawner.enemies, deltaTime);
                if (tileCollision.CheckCollision(player.GetBoundingBox())) {
                    player.playerPosition = oldPosition; // Revert to old position if collision detected
                }
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
                    tileCollision.Draw();
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

        // Start ImGui frame
            rlImGuiBegin();

            // Create ImGui window
            ImGui::Begin("Debug Window");
            ImGui::Text("Player Health: %i", player.healthPoints);
            ImGui::Text("Elapsed Time: %i seconds", (int)player.elapsedTime);
            ImGui::Text("Player Level: %i", player.level);
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