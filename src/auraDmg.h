#pragma once
#include <raylib.h>

class Player;
class Enemy;

class AuraDmg
{
    public:
        AuraDmg(float radius, int baseDamage, Color color);
        void Update(const Player& player);
        void Draw(const Player& player) const;
        bool Collision(const Vector2& playerPosition, Enemy& enemy);
    
    private:
        float radius;
        int baseDamage;
        Color color;
        
};