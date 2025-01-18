#include "abilityManager.h"
#include "ability.h"
#include "player.h"

AbilityManager::AbilityManager()
{
}

void AbilityManager::Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    for (auto& ability : abilities) {
        ability->Update(player, enemies, deltaTime);
    }
}

void AbilityManager::CheckCollisions(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies)
{
    for (auto& ability : abilities) {
        for (auto& enemy : enemies) {
            ability->CheckCollision(player, *enemy);
        }
    }
}

void AbilityManager::Draw(const Player& player) const
{
    for (const auto& ability : abilities) {
        ability->Draw(player);
    }
}

void AbilityManager::AddAbility(std::unique_ptr<Ability> ability)
{
    abilities.push_back(std::move(ability));
}
