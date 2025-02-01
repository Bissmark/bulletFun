#pragma once
#include <raylib.h>
#include "player.h"
#include "enemy.h"
#include <string>

class Ability
{
    public:
        virtual ~Ability() = default;
        virtual void Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime) = 0;
        virtual void Draw(const Player& player, const Camera2D& camera) const = 0;
        virtual bool CheckCollision(const Player& player, Enemy& enemy) = 0;
        virtual std::string GetName() const = 0;
        virtual float GetCooldownTime() const = 0;
        virtual float GetCooldownDuration() const = 0;
};