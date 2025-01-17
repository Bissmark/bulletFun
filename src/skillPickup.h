#pragma once
#include <raylib.h>
#include <vector>

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
        void Update(Player& player);
        void Draw() const;

    private:
        void CheckCollision(Player& player, Pickup& pickup);
        std::vector<Pickup> pickups;
};