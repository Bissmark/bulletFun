#include "skillPickup.h"
#include "player.h"
#include "auraDmg.h"
#include "flamethrower.h"

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

        switch (skillType) {
            case SkillType::Ring:
                player.AddAbility(std::make_unique<AuraDmg>(50.0f, 10, RED));
                break;
            case SkillType::Flamethrower:
                player.AddAbility(std::make_unique<Flamethrower>(20.0f, 100.0f, 30, 1, RED));
                break;
        }
    }
}

void SkillPickup::Draw() const
{
    if (isActive) DrawRectangle(skillPosition.x, skillPosition.y, 20, 20, RED);
}