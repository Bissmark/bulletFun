#include "powerup.h"
#include "player.h"
#include "terrainCollisionDetection.h"
#include <raylib.h>

Powerup::Powerup(Texture2D texture, float scale)
    : healthPot(texture), scale(scale), isActive(false), isCollected(false)
{
    Respawn();
}

void Powerup::Update(Player& player, TerrainCollision& terrainCollision)
{
    if (isActive) {
        CheckCollision(player, terrainCollision);
    } else {
        SpawnPowerup(terrainCollision);
    }
}

void Powerup::CheckCollision(Player& player, TerrainCollision& terrainCollision)
{
    Rectangle playerCollision = { player.playerPosition.x + player.frameRec.width / 2, player.playerPosition.y + player.frameRec.height / 2, (float)player.radius * 2, (float)player.radius * 2 };

    if (CheckCollisionRecs(boxCollision, playerCollision)) {
        isCollected = true;
        // increase player health by % of player max health
        player.healthPoints += player.maxHealth * 0.1;
        isActive = false;
        SpawnPowerup(terrainCollision);
    }
}

void Powerup::Respawn()
{
    powerupPosition = { (float)GetRandomValue(0, GetScreenWidth() - healthPot.width), (float)GetScreenHeight() - healthPot.height };
    boxCollision = { powerupPosition.x, powerupPosition.y, (float)healthPot.width, (float)healthPot.height };
    isActive = true;
    isCollected = false;
}

void Powerup::SpawnPowerup(TerrainCollision& terrainCollision)
{
    bool validPosition = false;
    Rectangle terrainBounds = terrainCollision.GetTerrainBounds();
    while (!validPosition) {
        // Generate a random position within the terrain bounds
        float x = (float)GetRandomValue(terrainBounds.x, terrainBounds.x + terrainBounds.width);
        float y = (float)GetRandomValue(terrainBounds.y, terrainBounds.y + terrainBounds.height);
        Rectangle boxCollision = { x, y, (float)healthPot.width * scale, (float)healthPot.height * scale };

        // Check if the position collides with any terrain colliders
        if (!terrainCollision.CheckCollision(boxCollision)) {
            powerupPosition = { x, y };
            this->boxCollision = boxCollision;
            isActive = true;
            isCollected = false;
            validPosition = true;
        }
    }
}

void Powerup::Draw() const
{
    if (isActive) {
        DrawTexturePro(healthPot, { 0, 0, (float)healthPot.width, (float)healthPot.height }, { powerupPosition.x, powerupPosition.y, (float)healthPot.width * scale, (float)healthPot.height * scale }, { (float)healthPot.width * scale / 2, (float)healthPot.height * scale / 2 }, 0.0f, WHITE);
    }
}