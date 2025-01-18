#pragma once
#include <raylib.h>
#include "player.h"
#include "enemy.h"

class Ability
{
    public:
        virtual ~Ability() = default;
        virtual void Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime) = 0;
        virtual void Draw(const Player& player) const = 0;
        virtual bool CheckCollision(const Player& player, Enemy& enemy) = 0;
};