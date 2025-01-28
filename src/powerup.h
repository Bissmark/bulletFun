#pragma once
#include <raylib.h>
#include "terrainCollisionDetection.h"

class Player;

class Powerup
{
    public:
        Powerup(Texture2D texture, float scale);
        Vector2 powerupPosition;
        int radius;
        void Update(Player& player, TerrainCollision& terrainCollision);
        void Draw() const;
        void CheckCollision(Player& player, TerrainCollision& terrainCollision);
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

        void SpawnPowerup(TerrainCollision& terrainCollision);
};