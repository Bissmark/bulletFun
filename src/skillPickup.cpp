#include "skillPickup.h"
#include "player.h"
#include "auraDmg.h"
#include "flamethrower.h"

SkillPickup::SkillPickup()
{
    // Initialize pickups
    pickups.push_back({ { (float)GetRandomValue(0, GetScreenWidth()), (float)GetRandomValue(0, GetScreenHeight()) }, { 0, 0, 20, 20 }, true, Pickup::SkillType::Flamethrower });
    pickups.push_back({ { (float)GetRandomValue(0, GetScreenWidth()), (float)GetRandomValue(0, GetScreenHeight()) }, { 0, 0, 20, 20 }, true, Pickup::SkillType::Ring });

    // Update boxCollision for each pickup
    for (auto& pickup : pickups) {
        pickup.boxCollision = { pickup.position.x, pickup.position.y, 20, 20 };
    }
}

void SkillPickup::Update(Player& player, SkillBar& skillBar)
{
    // for (auto& pickup : pickups) {
    //     if (pickup.isActive) {
    //         SpawnPickup(pickup, tileCollision);
    //     }
    // }

    for (auto& pickup : pickups) {
        if (pickup.isActive) {
            CheckCollision(player, pickup, skillBar);
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

// void SkillPickup::SpawnPickup(Pickup& pickup, TerrainCollision& terrainCollision)
// {
//     bool validPosition = false;
//     while (!validPosition) {
//         // Generate a random position within the terrain bounds
//         float x = (float)GetRandomValue(0, GetScreenWidth());
//         float y = (float)GetRandomValue(0, GetScreenHeight());
//         Rectangle boxCollision = { x, y, 20 * scale, 20 * scale };

//         // Check if the position collides with any terrain colliders
//         if (!terrainCollision.CheckCollision(boxCollision)) {
//             pickup.position = { x, y };
//             pickup.boxCollision = boxCollision;
//             pickup.isActive = true;
//             validPosition = true;
//         }
//     }
// }

void SkillPickup::Draw() const
{
    for (const auto& pickup : pickups) {
        if (pickup.isActive) {
            DrawRectangle(pickup.position.x, pickup.position.y, pickup.boxCollision.width, pickup.boxCollision.height, RED);
        }
    }
}