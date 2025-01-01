#include "powerup.h"
#include "player.h"

Powerup::Powerup()
    : radius(15)
    , powerupPosition({ 0 })
    , isActive(true)
    , isCollected(false)
    , speedX(5)
    , speedY(5)
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    healthPot = LoadTexture("src/Spritesheet/powerup/Health.png");
    speedPot = LoadTexture("src/Spritesheet/powerup/Speed.png");
    dmgPot = LoadTexture("src/Spritesheet/powerup/Damage.png");
    shieldPot = LoadTexture("src/Spritesheet/powerup/Shield.png");

    powerupPosition = { (float)GetRandomValue(0, screenWidth - healthPot.width), (float)GetRandomValue(0, screenHeight - healthPot.height) };
    boxCollision = { powerupPosition.x, powerupPosition.y, (float)healthPot.width, (float)healthPot.height };
}

void Powerup::Update(Player& player)
{
    CheckCollision(player);
}

void Powerup::CheckCollision(Player& player)
{
     Rectangle playerCollision = { player.playerPosition.x - player.radius, player.playerPosition.y - player.radius, (float)player.radius * 2, (float)player.radius * 2 };

    if (CheckCollisionRecs(boxCollision, playerCollision)) {
        isCollected = true;
        player.healthPoints += 10;
        isActive = false;
        Respawn();
    }
}

void Powerup::Respawn()
{
    powerupPosition = { (float)GetRandomValue(0, GetScreenWidth() - healthPot.width), (float)GetRandomValue(0, GetScreenHeight() - healthPot.height) };
    boxCollision = { powerupPosition.x, powerupPosition.y, (float)healthPot.width, (float)healthPot.height };
    isActive = true;
    isCollected = false;
}   

void Powerup::Draw() const
{
    if (isActive) {
        DrawTexture(healthPot, powerupPosition.x, powerupPosition.y, WHITE);
    }
}

