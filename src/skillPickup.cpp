#include "skillPickup.h"
#include "player.h"
#include "auraDmg.h"
#include "flamethrower.h"
#include <iostream>

SkillPickup::SkillPickup() : scale(0.8f)
{
    // Initialize pickups without assigning positions
    pickups.push_back({ { 0, 0 }, { 0, 0, 20, 20 }, false, Pickup::SkillType::Flamethrower });
    pickups.push_back({ { 0, 0 }, { 0, 0, 20, 20 }, false, Pickup::SkillType::Ring });
}


void SkillPickup::Update(Player& player, SkillBar& skillBar, TerrainCollision& tileCollision)
{
    for (auto& pickup : pickups) {
        if (pickup.isActive) {
            CheckCollision(player, pickup, skillBar);
        } else {
            SpawnPickup(pickup, tileCollision);
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
                //player.AddAbility(std::make_unique<AuraDmg>(50.0f, 10, RED));
                skillBar.AddSkill(std::make_unique<AuraDmg>(100.0f, 1, RED));
                break;
            case Pickup::SkillType::Flamethrower:
                //player.AddAbility(std::make_unique<Flamethrower>(20.0f, 100.0f, 20, 1, RED));
                skillBar.AddSkill(std::make_unique<Flamethrower>(20.0f, 100.0f, 20, 1, RED));
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

        // Update the pickup position and collision box
        pickup.position = { x, y };
        pickup.boxCollision = { x, y, pickup.boxCollision.width, pickup.boxCollision.height };

        // Check if the new position is valid (not colliding with terrain)
        if (!terrainCollision.CheckCollision(pickup.boxCollision)) {
            //if (!terrainCollision.CheckCollisionTiles(pickup.boxCollision)) {
                validPosition = true;
                pickup.isActive = true;
           // }
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