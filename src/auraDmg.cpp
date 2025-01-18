#include "auraDmg.h"
// #include "player.h"
// #include "enemy.h"
#include <raymath.h>
#include <iostream>

AuraDmg::AuraDmg(float radius, int baseDamage, Color color)
    : maxRadius(radius), currentRadius(radius), baseDamage(baseDamage), color(color), enemy(enemy)
{
    currentRadius = 0.0f;
}

void AuraDmg::Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    if (cooldownTime > 0.0f) {
        cooldownTime -= deltaTime;
    }

    std::cout << isActive << std::endl;

    if (isActive) {
        elapsedTime += deltaTime;

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
            float distance = Vector2Distance(enemy->enemyPosition, player.playerPosition);
            if (distance <= currentRadius) {
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
    float distance = Vector2Distance(enemy.enemyPosition, player.playerPosition);
    if (distance <= currentRadius) {
        enemy.health -= baseDamage;
        if (enemy.health <= 0) {
            enemy.Destroy();
        }
        return true;
    }
    return false;
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

void AuraDmg::Draw(const Player& player) const
{
    if (isActive) {
        Vector2 centerPosition = { player.playerPosition.x + player.frameRec.width / 2, player.playerPosition.y + player.frameRec.height / 2 };
        DrawCircleV(centerPosition, currentRadius, Fade(color, 0.5f));
    }
}