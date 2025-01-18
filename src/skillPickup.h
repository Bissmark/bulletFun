#pragma once
#include <raylib.h>
#include <vector>
#include "skillBar.h"

class Player;

struct Pickup {
    Vector2 position;
    Rectangle boxCollision;
    bool isActive;
    enum class SkillType { Ring, Flamethrower } skillType;
};

class SkillPickup
{
    public:
        SkillPickup();
        void Update(Player& player, SkillBar& skillBar);
        void Draw() const;

    private:
        void CheckCollision(Player& player, Pickup& pickup, SkillBar& skillBar);
        std::vector<Pickup> pickups;
};