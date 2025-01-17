#pragma once
#include "ability.h"

class AuraDmg : public Ability
{
    public:
        AuraDmg(float radius, int baseDamage, Color color);
        void Update(const Player& player);
        void Draw(const Player& player) const;
        bool CheckCollision(const Player& player, Enemy& enemy);
    
    private:
        float radius;
        int baseDamage;
        Color color;
        
};