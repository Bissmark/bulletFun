#include "skillPickup.h"
#include "player.h"
#include <iostream>

SkillPickup::SkillPickup() : scale(0.8f)
{
    // Initialize pickups without assigning positions
    pickups.push_back({ { 0, 0 }, { 0, 0, 20, 20 }, false, false, Pickup::SkillType::FireBreath });
    pickups.push_back({ { 0, 0 }, { 0, 0, 20, 20 }, false, false, Pickup::SkillType::Ring });
    pickups.push_back({ { 0, 0 }, { 0, 0, 20, 20 }, false, false, Pickup::SkillType::RotatingBalls });
    pickups.push_back({ { 0, 0 }, { 0, 0, 20, 20 }, false, false, Pickup::SkillType::Blizzard });
}


void SkillPickup::Update(Player& player, SkillBar& skillBar, TerrainCollision& tileCollision)
{
    for (auto& pickup : pickups) {
        if (pickup.isActive) {
            CheckCollision(player, pickup, skillBar);
        } else if (!pickup.hasSpawned) {
            SpawnPickup(pickup, tileCollision);
            pickup.hasSpawned = true;
        }
    }
}

void SkillPickup::CheckCollision(Player& player, Pickup& pickup, SkillBar& skillBar)
{
    Rectangle playerCollision = player.GetBoundingBox();
    
    if (CheckCollisionRecs(pickup.boxCollision, playerCollision)) {
        pickup.isActive = false;

        switch (pickup.skillType) {
            case Pickup::SkillType::Ring:
                skillBar.AddSkill(std::make_unique<AuraDmg>(100.0f, 10, RED));
                break;
            case Pickup::SkillType::FireBreath:
                skillBar.AddSkill(std::make_unique<FireBreath>(20.0f, 20.0f, 10, 1, RED));
                break;
            case Pickup::SkillType::RotatingBalls:
                skillBar.AddSkill(std::make_unique<RotatingBalls>(5.0f, 5, 30.0f, 3, 5, RED));
                break;
            case Pickup::SkillType::Blizzard:
                skillBar.AddSkill(std::make_unique<Blizzard>(50.0f, 5, 10, BLUE));
                break;
        }
    }
}

void SkillPickup::SpawnPickup(Pickup& pickup, TerrainCollision& terrainCollision)
{
    bool validPosition = false;
    Rectangle terrainBounds = terrainCollision.GetTerrainBounds();
    
    while (!validPosition) {
        // Generate a random position within the terrain bounds
        float x = (float)GetRandomValue(terrainBounds.x, terrainBounds.x + terrainBounds.width - pickup.boxCollision.width);
        float y = (float)GetRandomValue(terrainBounds.y, terrainBounds.y + terrainBounds.height - pickup.boxCollision.height);

        // Update the pickup's collision box
        Rectangle boxCollision = { x, y, pickup.boxCollision.width, pickup.boxCollision.height };

        // Check if the new position collides with walls or tiles
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
                                break; // Stop checking if a collision is found
                            }
                        }
                    }
                }
            }

            // If no tile collision, finalize placement
            if (!tileCollision) {
                pickup.position = { x, y };
                pickup.boxCollision = boxCollision;
                pickup.isActive = true;
                validPosition = true;
            }
        }
    }
}



void SkillPickup::Draw() const
{
    for (const auto& pickup : pickups) {
        if (pickup.isActive) {
            DrawRectangle(pickup.position.x, pickup.position.y, pickup.boxCollision.width * scale, pickup.boxCollision.height * scale, RED);
        }
    }
}