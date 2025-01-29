#include "powerup.h"
#include "player.h"
#include "terrainCollisionDetection.h"
#include <raylib.h>
#include <iostream>

Powerup::Powerup(Texture2D texture, float scale)
    : healthPot(texture), scale(scale)
{
    // Initialize 100 powerups
    for (int i = 0; i < 100; ++i) {
        PowerupInstance powerup = { { 0, 0 }, { 0, 0, (float)healthPot.width * scale, (float)healthPot.height * scale }, false, false };
        powerups.push_back(powerup);
    }
}

void Powerup::Update(Player& player, TerrainCollision& terrainCollision)
{
    for (auto& powerup : powerups) {
        // std::cout << "Updating powerups..." << powerup.isActive << std::endl;
        if (powerup.isActive) {
            CheckCollision(player, terrainCollision);
            //terrainCollision.CheckCollisionTiles(powerup.boxCollision);
        } else {
            SpawnPowerup(terrainCollision);
        }
    }
}

void Powerup::CheckCollision(Player& player, TerrainCollision& terrainCollision)
{
    Rectangle playerCollision = { player.playerPosition.x + player.frameRec.width / 2, player.playerPosition.y + player.frameRec.height / 2, (float)player.radius * 2, (float)player.radius * 2 };

    for (auto& powerup : powerups) {
        if (powerup.isActive && CheckCollisionRecs(powerup.boxCollision, playerCollision)) {
            powerup.isCollected = true;
            // increase player health by % of player max health
            player.healthPoints += player.maxHealth * 0.1;
            powerup.isActive = false;
            SpawnPowerup(terrainCollision);
        }
    }
}

void Powerup::SpawnPowerup(TerrainCollision& terrainCollision)
{
    for (auto& powerup : powerups) {
        if (!powerup.isActive) {
            bool validPosition = false;
            Rectangle terrainBounds = terrainCollision.GetTerrainBounds();
            while (!validPosition) {
                float x = (float)GetRandomValue(terrainBounds.x, terrainBounds.x + terrainBounds.width - healthPot.width);
                float y = (float)GetRandomValue(terrainBounds.y, terrainBounds.y + terrainBounds.height - healthPot.height);
                Rectangle boxCollision = { x, y, (float)healthPot.width * scale, (float)healthPot.height * scale };

                //DrawRectangleLines(x, y, boxCollision.width, boxCollision.height, BLUE);

                // Check if the powerup collides with walls or tiles
                if (!terrainCollision.CheckCollision(boxCollision)) {
                    bool tileCollision = false;
                    
                    // Iterate over the tile objects in the collision layer
                    if (terrainCollision.map != nullptr && terrainCollision.map->layersLength > 1) {
                        TmxLayer* collisionLayer = &terrainCollision.map->layers[1];
                        if (collisionLayer->type == LAYER_TYPE_OBJECT_GROUP) {
                            for (uint32_t i = 0; i < collisionLayer->exact.objectGroup.objectsLength; ++i) {
                                TmxObject* object = &collisionLayer->exact.objectGroup.objects[i];
                                if (object->type == OBJECT_TYPE_TILE) {
                                    if (terrainCollision.CheckCollisionTiles(boxCollision, object)) {
                                        tileCollision = true;
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    // If no tile collision, place the powerup
                    if (!tileCollision) {
                        powerup.position = { x, y };
                        powerup.boxCollision = boxCollision;
                        powerup.isActive = true;
                        powerup.isCollected = false;
                        validPosition = true;
                    }
                }
            }
        }
    }
}



void Powerup::Draw() const
{
    for (const auto& powerup : powerups) {
        if (powerup.isActive) {
            DrawTexturePro(healthPot, { 0, 0, (float)healthPot.width, (float)healthPot.height }, { powerup.position.x, powerup.position.y, (float)healthPot.width * scale, (float)healthPot.height * scale }, { (float)healthPot.width * scale / 2, (float)healthPot.height * scale / 2 }, 0.0f, WHITE);
        }
    }
}