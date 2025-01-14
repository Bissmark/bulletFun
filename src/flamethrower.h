#pragma once
#include <raylib.h>
#include <vector>

class Player;
class Enemy;

class Flamethrower
{
    public:
        Flamethrower(float width, float length, int speed, int baseDamage, Color color);
        void Update(const Player& player);
        void Draw(const Player& player) const;
        bool Collision(const Player& player, Enemy& enemy);

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