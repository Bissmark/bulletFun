#include "powerup.h"

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

}

void Powerup::Update()
{
    //CheckCollision();
}

void Powerup::Draw() const
{
    if (isActive) {
        DrawTexture(healthPot, powerupPosition.x, powerupPosition.y, WHITE);
    }
}