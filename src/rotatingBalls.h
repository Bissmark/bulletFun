#pragma once
#include "ability.h"
#include <string>
#include <vector>
#include <memory>

class RotatingBalls : public Ability
{
    public:
        RotatingBalls(float cooldown, float radius, float speed, int numBalls);
        void Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime) override;
        void Draw(const Player& player, const Camera2D& camera) const;
        bool CheckCollision(const Player& player, Enemy& enemy) override;
        void Activate();
        std::string GetName() const override;
        float GetCooldownTime() const;
        float GetCooldownDuration() const;


    private:
        struct Ball {
            Vector2 position;
            Vector2 velocity;
            bool isActive;
        };

        std::vector<Ball> balls;
        float cooldown;
        float cooldownTime;
        float radius;
        float speed;
        int numBalls;
        bool isActive;
        std::string name;
};