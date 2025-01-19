#include "flamethrower.h"
#include <raymath.h>
#include <cmath>

Flamethrower::Flamethrower(float width, float length, int speed, int baseDamage, Color color)
    : width(width), length(length), speed(speed), baseDamage(baseDamage), color(color), rotationAngle(0.0f)
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
    Vector2 screenPlayerPosition = GetWorldToScreen2D(centerPosition, camera);

    for (int i = 0; i < numBeams; ++i) {
        float angle = beamAngles[i];
        Vector2 forwardOffset = { cosf(angle * DEG2RAD) * (player.frameRec.width + (width * 1.5)), sinf(angle * DEG2RAD) * (player.frameRec.height + (width * 1.5)) };
        Vector2 beamPosition = Vector2Add(screenPlayerPosition, forwardOffset);
        DrawRectanglePro({ beamPosition.x, beamPosition.y, length, width }, { length / 2, width / 2 }, angle, color);
    }
}

bool Flamethrower::CheckCollision(const Player& player, Enemy& enemy)
{
    Vector2 centerPosition = player.playerPosition;

    for (int i = 0; i < numBeams; ++i) {
        float angle = beamAngles[i];
        Vector2 forwardOffset = { cosf(angle * DEG2RAD) * (player.frameRec.width / 2 + width / 2), sinf(angle * DEG2RAD) * (player.frameRec.height / 2 + width / 2) };
        Vector2 beamPosition = Vector2Add(centerPosition, forwardOffset);
        Rectangle beamCollision = { beamPosition.x - length / 2, beamPosition.y - width / 2, length, width };
        if (CheckCollisionRecs(beamCollision, enemy.boxCollision)) {
            enemy.health -= baseDamage;
            if (enemy.health <= 0) {
                enemy.Destroy();
            }
            return true;
        }
    }
    return false;
}