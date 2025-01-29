#include "powerup.h"
#include "player.h"
#include "terrainCollisionDetection.h"
#include <raylib.h>
#include <iostream>

Powerup::Powerup(Texture2D texture, float scale)
    : healthPot(texture), scale(scale), isActive(false), isCollected(false)
{
    // Initialize 100 powerups
    // for (int i = 0; i < 100; ++i) {
    //     PowerupInstance powerup = { { 0, 0 }, { 0, 0, (float)healthPot.width * scale, (float)healthPot.height * scale }, false, false };
    //     powerups.push_back(powerup);
    // }
    //Respawn();
}

void Powerup::Update(Player& player, TerrainCollision& terrainCollision)
{
    //for (auto& powerup : powerups) {
        // std::cout << "Updating powerups..." << powerup.isActive << std::endl;
        if (isActive) {
            CheckCollision(player, terrainCollision);
            //terrainCollision.CheckCollisionTiles(powerup.boxCollision);
        } else {
            SpawnPowerup(terrainCollision);
        }
    //}
}

void Powerup::Respawn()
{
    // position = { (float)GetRandomValue(0, GetScreenWidth() - healthPot.width), (float)GetScreenHeight() - healthPot.height };
    boxCollision = { position.x, position.y, (float)healthPot.width * scale, (float)healthPot.height * scale };
    isActive = true;
    isCollected = false;
}

void Powerup::CheckCollision(Player& player, TerrainCollision& terrainCollision)
{
    Rectangle playerCollision = player.GetBoundingBox();

    //for (auto& powerup : powerups) {
        if (CheckCollisionRecs(boxCollision, playerCollision)) {
            isCollected = true;
            // increase player health by % of player max health
            player.healthPoints += player.maxHealth * 0.1;
            isActive = false;
            SpawnPowerup(terrainCollision);
        }
    //}
}

void Powerup::SpawnPowerup(TerrainCollision& terrainCollision)
{
    //for (auto& powerup : powerups) {
        if (!isActive) {
            bool validPosition = false;
            Rectangle terrainBounds = terrainCollision.GetTerrainBounds();
            while (!validPosition) {
                position.x = (float)GetRandomValue(terrainBounds.x, terrainBounds.x + terrainBounds.width - healthPot.width);
                position.y = (float)GetRandomValue(terrainBounds.y, terrainBounds.y + terrainBounds.height - healthPot.height);
                Rectangle boxCollision = { position.x, position.y, (float)healthPot.width * scale, (float)healthPot.height * scale };

                //DrawRectangleLines(position.x, position.y, boxCollision.width, boxCollision.height, BLUE);

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
                        this->position = { position.x, position.y };
                        this->boxCollision = boxCollision;
                        this->isActive = true;
                        this->isCollected = false;
                        validPosition = true;
                    }
                }
            }
        }
    //}
}

void Powerup::Draw() const
{
    if (isActive) {
        // Draw the powerup texture
        DrawTexturePro(healthPot, 
                       { 0, 0, (float)healthPot.width, (float)healthPot.height }, 
                       { position.x, position.y, (float)healthPot.width * scale, (float)healthPot.height * scale }, 
                       { 0, 0 },  // No offset
                       0.0f, 
                       WHITE);
    }
}
