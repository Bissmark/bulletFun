#pragma once
#include <raylib.h>
#include <vector>
#include "skillBar.h"
#include "terrainCollisionDetection.h"

class Player;

struct Pickup {
    Vector2 position;
    Rectangle boxCollision;
    bool isActive;
    bool hasSpawned;
    enum class SkillType { Ring, FireBreath, RotatingBalls } skillType;
};

class SkillPickup
{
    public:
        SkillPickup();
        //void Update(Player& player, SkillBar& skillBar);
        void Update(Player& player, SkillBar& skillBar, TerrainCollision& tileCollision);
        void Draw() const;

    private:
        void CheckCollision(Player& player, Pickup& pickup, SkillBar& skillBar);
        std::vector<Pickup> pickups;
        float scale;

        void SpawnPickup(Pickup& pickup, TerrainCollision& tileCollision);
};