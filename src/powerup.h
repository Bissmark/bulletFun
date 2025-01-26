#pragma once
#include <raylib.h>

class Player;

class Powerup
{
    public:
        Powerup();
        Vector2 powerupPosition;
        int radius;
        void Update(Player& player);
        void Draw() const;
        void CheckCollision(Player& player);
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
        float scale;
};