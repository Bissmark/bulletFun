#pragma once
#include "ability.h"
#include <vector>

class Flamethrower : public Ability
{
    public:
        Flamethrower(float width, float length, int speed, int baseDamage, Color color);
        void Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime) override;
        void Draw(const Player& player) const override;
        bool CheckCollision(const Player& player, Enemy& enemy);

    private:
        float width;
        float length;
        int speed;
        int baseDamage;
        Color color;
        int numBeams;
        float rotationAngle;
        std::vector<float> beamAngles;
};