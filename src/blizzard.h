#pragma once
#include "ability.h"

class Blizzard : public Ability
{
    public:
        Blizzard(float radius, int speed, int baseDamage, Color color);
        void Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime) override;
        void Draw(const Player& player, const Camera2D& camera) const;
        bool CheckCollision(const Player& player, Enemy& enemy);
        float GetCooldownTime() const override;
        float GetCooldownDuration() const override;
        std::string GetName() const override;
        int GetDamage() const override;
        void Activate() override;
        void SetCastPosition(Vector2 position);
        void SetFixedScreenPosition(Vector2 fixedPos);
        Vector2 GetFixedScreenPosition() const;
        Shader blizzardShader;
        Vector2 castPosition;

    private: 
        Vector2 centerPosition;
        Vector2 fixedScreenPosition;
        int speed;
        int baseDamage;
        float radius;
        float cooldown;
        float cooldownTime;
        float elapsedTime;
        bool isActive;
        float activeTime;
        Color color;
        float blizzardTime;
        bool positionSet = false;
        std::string name;
};