#pragma once
#include <raylib.h>

class Powerup
{
    public:
        Powerup();
        Vector2 powerupPosition;
        int radius;
        void Update();
        void Draw() const;
        void CheckCollision();
        void Respawn();
        bool isActive;
        bool isCollected;

    private:
        Texture2D healthPot;
        Texture2D speedPot;
        Texture2D dmgPot;
        Texture2D shieldPot;
        Rectangle frameRec;
        Rectangle boxCollision;
        int speedX;
        int speedY;
};