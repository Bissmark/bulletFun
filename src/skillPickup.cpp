#include "skillPickup.h"
#include "player.h"

SkillPickup::SkillPickup() : skillPosition({ 0 }), isActive(true)
{
    skillPosition = { (float)GetRandomValue(0, GetScreenWidth()) };
    boxCollision = { skillPosition.x, skillPosition.y, 20, 20 };
}

void SkillPickup::Update(Player& player)
{
    CheckCollision(player);
}

void SkillPickup::CheckCollision(Player& player)
{
    Rectangle playerCollision = { player.playerPosition.x - player.radius, player.playerPosition.y - player.radius, (float)player.radius * 2, (float)player.radius * 2 };

    if (CheckCollisionRecs(boxCollision, playerCollision)) {
        isActive = false;
    }
}

void SkillPickup::Draw() const
{
    if (isActive) DrawRectangle(skillPosition.x, skillPosition.y, 20, 20, RED);
}