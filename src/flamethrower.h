#pragma once
#include "ability.h"
#include <vector>
#include <string>

class Flamethrower : public Ability
{
    public:
        Flamethrower(float width, float length, int speed, int baseDamage, Color color);
        void Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime) override;
        void Draw(const Player& player, const Camera2D& camera) const;
        bool CheckCollision(const Player& player, Enemy& enemy);
        std::string GetName() const override;

    private:
        float width;
        float length;
        int speed;
        int baseDamage;
        Color color;
        int numBeams;
        float rotationAngle;
        Vector2 centerPosition;
        std::string name;
        std::vector<float> beamAngles;
};