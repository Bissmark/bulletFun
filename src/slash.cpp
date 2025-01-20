#include "slash.h"
#include "player.h"
#include "enemy.h"
#include <raymath.h>

Slash::Slash(Vector2 position, Vector2 direction, float radius, Player* player) 
    : position(position)
    , direction(direction)
    , radius(radius)
    , player(player)
{
    slashTexture = LoadTexture("Spritesheet/Slash.png");
}

void Slash::Update()
{
    
}

bool Slash::Collision(Enemy& enemy)
{
    float distance = Vector2Distance(position, enemy.enemyPosition);
    if (distance <= radius) {
        int damage = player->baseDamage;
        if (GetRandomValue(1, 100) <= player->critChance) {
            damage *= 2;
        }
        enemy.health -= damage;
        if (enemy.health <= 0) {
            enemy.Destroy();
        }
        return true;
    }
    return false;
}

// If I want to do the slash infront of the enemy
// bool Slash::Collision(Enemy& enemy)
// {
//     float distance = Vector2Distance(position, enemy.enemyPosition);
//     if (distance <= radius) {
//         Vector2 toEnemy = Vector2Subtract(enemy.enemyPosition, position);
//         toEnemy = Vector2Normalize(toEnemy);
//         float dotProduct = Vector2DotProduct(direction, toEnemy);
//         float angle = acosf(dotProduct) * (180.0f / PI);
//         if (angle <= 45.0f) { // Only consider enemies within a 90-degree cone in front of the player
//             int damage = player->baseDamage;
//             if (GetRandomValue(1, 100) <= player->critChance) {
//                 damage *= 2;
//             }
//             enemy.health -= damage;
//             if (enemy.health <= 0) {
//                 enemy.Destroy();
//             }
//             return true;
//         }
//     }
//     return false;
// }

void Slash::Draw() const
{
    DrawCircleV(position, radius, Fade(RED, 0.5f)); // Draw the slash area
}