#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include <raymath.h>
#include <iostream>

Bullet::Bullet(Vector2 position, Vector2 direction, float speed, Color color)
{
    this->position = position;
    this->direction = direction;
    this->speed = speed;
    this->color = color;
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