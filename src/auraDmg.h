#pragma once
#include "ability.h"

class AuraDmg : public Ability
{
    public:
        AuraDmg(float radius, int baseDamage, Color color);
        void Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime) override;
        void Draw(const Player& player) const override;
        bool CheckCollision(const Player& player, Enemy& enemy) override;
        void Activate();
    
    private:
        Enemy& enemy;
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
        
};