#pragma once
#include "ability.h"
#include "player.h"
#include <vector>
#include <string>

class FireBreath : public Ability
{
    public:
        FireBreath(float width, float length, int speed, int baseDamage, Color color);
        void Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime) override;
        void Draw(const Player& player, const Camera2D& camera) const;
        bool CheckCollision(const Player& player, Enemy& enemy);
        float GetCooldownTime() const override;
        float GetCooldownDuration() const override;
        std::string GetName() const override;
        int GetDamage() const override;
        void Activate() override;

    private:
        Vector2 centerPosition;
        int speed;
        int baseDamage;
        int numSections;
        int maxSections;
        float length;
        float width;
        float rotationAngle;
        float cooldown;
        float cooldownTime;
        float elapsedTime;
        bool isActive;
        float storedAngle;
        Color color;
        std::string name;
        std::vector<float> beamAngles;
};