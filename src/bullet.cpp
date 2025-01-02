#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include <raymath.h>
#include <iostream>

Bullet::Bullet(Vector2 position, Vector2 direction, float speed, Color color)
{
    this->position = position;
    this->direction = Vector2Normalize(direction);
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
    Rectangle bulletCollision = { position.x, position.y, 5, 5 };

    if (CheckCollisionRecs(bulletCollision, enemy.boxCollision)) {
        return true;
    }
    return false;
}

void Bullet::Draw() const
{
    DrawCircleV(position, 5, color);
}