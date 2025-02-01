#pragma once
#include "ability.h"
#include <string>
#include <unordered_map>

class AuraDmg : public Ability
{
    public:
        AuraDmg(float radius, int baseDamage, Color color);
        void Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime) override;
        void Draw(const Player& player, const Camera2D& camera) const;
        bool CheckCollision(const Player& player, Enemy& enemy) override;
        std::string GetName() const override;
        float GetCooldownTime() const override;
        float GetCooldownDuration() const override;
        void Activate() override;

    private:
        float maxRadius;
        float currentRadius;
        int baseDamage;
        Color color;
        bool isActive;
        float duration;
        float elapsedTime;
        float cooldown;
        float cooldownTime;
        float deltaTime;
        Vector2 centerPosition;
        std::string name;
        std::unordered_map<Enemy*, bool> hitEnemies;
        
};