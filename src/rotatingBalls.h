#pragma once
#include "ability.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_set>

class RotatingBalls : public Ability
{
    public:
        RotatingBalls(float cooldown, int baseDamage, float radius, float speed, int numBalls, Color color);
        void Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime) override;
        void Draw(const Player& player, const Camera2D& camera) const;
        bool CheckCollision(const Player& player, Enemy& enemy) override;
        std::string GetName() const override;
        float GetCooldownTime() const override;
        float GetCooldownDuration() const override;
        int GetDamage() const override;
        void Activate() override;


    private:
        struct Ball {
            Vector2 position;
            Vector2 velocity;
            float angle;
            bool isActive;
            std::unordered_set<Enemy*> hitEnemies;
        };

        std::vector<Ball> balls;
        float cooldown;
        float cooldownTime;
        float radius;
        Color color;
        float speed;
        int numBalls;
        bool isActive;
        bool isShooting;
        int baseDamage;
        std::string name;
};