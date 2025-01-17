#pragma once
#include <raylib.h>

class Player;

class SkillPickup
{
    public:
        SkillPickup();
        void Update(Player& player);
        void Draw() const;
        void CheckCollision(Player& player);

    private:
        Vector2 skillPosition;
        Rectangle boxCollision;
        bool isActive;
        enum Skills { Flamethrower, Ring };
};