#pragma once
#include <raylib.h>

class Player;

class SkillPickup
{
    public:
        SkillPickup();
        void Update(Player& player);
        void Draw() const;

    private:
        void CheckCollision(Player& player);
        Vector2 skillPosition;
        Rectangle boxCollision;
        bool isActive;
        enum class SkillType { Flamethrower, Ring } skillType;
};