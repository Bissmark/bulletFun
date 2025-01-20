#include "auraDmg.h"
// #include "player.h"
// #include "enemy.h"
#include <raymath.h>
#include <iostream>

AuraDmg::AuraDmg(float radius, int baseDamage, Color color)
    : maxRadius(radius), baseDamage(baseDamage), color(color), isActive(false), duration(2.0f), elapsedTime(0.0f), cooldown(5.0f), cooldownTime(0.0f), name("AuraDmg")
{
    currentRadius = 0.0f;
    centerPosition = { 0.0f, 0.0f };
}

void AuraDmg::Activate()
{
    if (cooldownTime <= 0.0f) {
        isActive = true;
        elapsedTime = 0.0f;
        currentRadius = 0.0f;
        cooldownTime = cooldown;
    }
}

void AuraDmg::Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    if (cooldownTime > 0.0f) {
        cooldownTime -= deltaTime;
    }

    if (isActive) {
        elapsedTime += deltaTime;

        centerPosition = { player.playerPosition.x + player.frameRec.width / 2, player.playerPosition.y + player.frameRec.height / 2 };

        // Calculate the current radius based on the elapsed time
        float halfDuration = duration / 2.0f;
        if (elapsedTime <= halfDuration) {
            currentRadius = maxRadius * (elapsedTime / halfDuration);
        } else if (elapsedTime <= duration) {
            currentRadius = maxRadius * ((duration - elapsedTime) / halfDuration);
        } else {
            isActive = false;
            currentRadius = 0.0f;
        }

        // Check for collisions with enemies
        for (auto& enemy : enemies) {
            if (CheckCollisionRecs(enemy->boxCollision, { centerPosition.x - currentRadius, centerPosition.y - currentRadius, currentRadius * 2, currentRadius * 2 })) {
                enemy->health -= baseDamage;
                if (enemy->health <= 0) {
                    enemy->Destroy();
                }
            }
        }
    }
}

bool AuraDmg::CheckCollision(const Player& player, Enemy& enemy)
{
    // float distance = Vector2Distance(enemy.enemyPosition, centerPosition);
    // if (distance <= currentRadius) {
    //     enemy.health -= baseDamage;
    //     if (enemy.health <= 0) {
    //         enemy.Destroy();
    //     }
    //     return true;
    // }
    // return false;
}

void AuraDmg::Draw(const Player& player, const Camera2D& camera) const
{
    if (isActive) {
        Vector2 screenPlayerPosition = GetWorldToScreen2D(centerPosition, camera);
        DrawCircleLinesV(screenPlayerPosition, currentRadius, Fade(color, 0.5f));
    }
}

std::string AuraDmg::GetName() const
{
    return name;
}