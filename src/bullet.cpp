#include "bullet.h"
#include <raymath.h>

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

void Bullet::Draw() const
{
    DrawCircleV(position, 5, color);
}