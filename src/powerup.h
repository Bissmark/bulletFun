#pragma once
#include <raylib.h>
#include "player.h"
#include "terrainCollisionDetection.h"
#include <vector>

class Powerup
{
public:
    Powerup(Texture2D texture, float scale);
    void Update(Player& player, TerrainCollision& terrainCollision);
    void CheckCollision(Player& player, TerrainCollision& terrainCollision);
    void SpawnPowerup(TerrainCollision& terrainCollision);
    void Draw() const;
    void Respawn();

private:
    Texture2D healthPot;
    float scale;
    bool isActive;
    bool isCollected;
    Rectangle boxCollision;
    Vector2 position;
    
    // struct PowerupInstance {
    //     Vector2 position;
    //     Rectangle boxCollision;
    //     bool isActive;
    //     bool isCollected;
    // };
    // std::vector<PowerupInstance> powerups;
};