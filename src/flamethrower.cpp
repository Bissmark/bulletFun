#include "flamethrower.h"
#include <raymath.h>
#include <cmath>

Flamethrower::Flamethrower(float width, float length, int speed, int baseDamage, Color color)
    : width(width), length(length), speed(speed), baseDamage(baseDamage), color(color), rotationAngle(0.0f), name("Flamethrower")
{
    centerPosition = { 0.0f, 0.0f };
    numBeams = 3;
    for (int i = 0; i < numBeams; ++i) {
        beamAngles.push_back(i * (360.0f / numBeams)); // Evenly distribute angles
    }
}

void Flamethrower::Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    centerPosition = { player.playerPosition.x + player.frameRec.width / 2, player.playerPosition.y + player.frameRec.height / 2 };
    rotationAngle += GetFrameTime() * speed;
    for (int i = 0; i < numBeams; ++i) {
        beamAngles[i] = fmod(rotationAngle + i * (360.0f / numBeams), 360.0f); // Update angles to be evenly distributed
    }
}

void Flamethrower::Draw(const Player& player, const Camera2D& camera) const
{
    Vector2 adjustedCenterPosition = {
            player.playerPosition.x + (player.frameRec.width * player.scale) / 2.0f,
            player.playerPosition.y + (player.frameRec.height * player.scale) / 2.0f
    };
    Vector2 screenPlayerPosition = GetWorldToScreen2D(adjustedCenterPosition, camera);

    for (int i = 0; i < numBeams; ++i) {
        float angle = beamAngles[i];
        Vector2 forwardOffset = { cosf(angle * DEG2RAD) * (player.frameRec.width + (width * 1.5)), sinf(angle * DEG2RAD) * (player.frameRec.height + (width * 1.5)) };
        Vector2 beamPosition = Vector2Add(screenPlayerPosition, forwardOffset);
        DrawRectanglePro({ beamPosition.x, beamPosition.y, length, width }, { length / 2, width / 2 }, angle, color);
    }
}

bool Flamethrower::CheckCollision(const Player& player, Enemy& enemy)
{
    
    // Adjust the center position based on the player's scale
    Vector2 adjustedCenterPosition = {
        player.playerPosition.x + (player.frameRec.width * player.scale) / 2.0f,
        player.playerPosition.y + (player.frameRec.height * player.scale) / 2.0f
    };

    // Calculate the collision rectangle for the flamethrower
    Rectangle flamethrowerRect = {
        adjustedCenterPosition.x - (width / 2.0f),
        adjustedCenterPosition.y - (length / 2.0f),
        width,
        length
    };

    // Check for collision with the enemy
    return CheckCollisionRecs(flamethrowerRect, enemy.GetBoundingBox());
}

std::string Flamethrower::GetName() const
{
    return name;
}

float Flamethrower::GetCooldownTime() const
{
    return cooldownTime;
}

float Flamethrower::GetCooldownDuration() const
{
    return cooldown;
}

void Flamethrower::Activate()
{
    if (cooldownTime <= 0.0f)
    {
        //isShooting = false; // Reset shooting state
        cooldownTime = cooldown;
    }
}