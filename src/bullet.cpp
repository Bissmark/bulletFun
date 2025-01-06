#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include <raymath.h>
#include <iostream>

Bullet::Bullet(Vector2 position, Vector2 direction, float speed, Color color, Player* player) : position(position), direction(direction), speed(speed), color(color), player(player)
{
}

void Bullet::Move()
{
    position.x += direction.x * speed;
    position.y += direction.y * speed;
}

bool Bullet::Collision(Enemy& enemy)
{
    Rectangle bulletCollision = { position.x - 2.5f, position.y - 2.5f, 5.0f, 5.0f };

    if (CheckCollisionRecs(bulletCollision, enemy.boxCollision)) {
        int damage = player->baseDamage;
        if (GetRandomValue(1, 100) <= player->critChance) { // 5% chance for critical hit
            damage *= 2; // Critical hit deals double damage
        }
        std::cout << "Player base damage: " << damage << std::endl;
        enemy.health -= damage;
        if (enemy.health <= 0) {
            enemy.Destroy();
        }
        return true;
    }
    return false;
}

void Bullet::Draw() const
{
    DrawCircleV(position, 5, color);
}