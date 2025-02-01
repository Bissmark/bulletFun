#include "abilityManager.h"

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

void AbilityManager::Draw(const Player& player, const Camera2D& camera) const
{
    for (const auto& ability : abilities) {
        ability->Draw(player, camera);
    }
}

void AbilityManager::AddAbility(std::unique_ptr<Ability> ability)
{
    abilities.push_back(std::move(ability));
}

const std::vector<std::unique_ptr<Ability>>& AbilityManager::GetAbilities() const
{
    return abilities;
}

