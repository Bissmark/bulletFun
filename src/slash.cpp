#include "slash.h"
#include "player.h"
#include "enemy.h"
#include <raymath.h>

Slash::Slash(Vector2 position, float radius, Player* player) 
    : position(position)
    , radius(radius)
    , player(player)
{
    slashTexture = LoadTexture("src/Spritesheet/Slash.png");
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

void Slash::Draw() const
{
    DrawCircleV(position, radius, Fade(RED, 0.5f)); // Draw the slash area
}