#include "bullet.h"

Bullet::Bullet(Vector2 position, float speed, Color color)
{
    this->position = position;
    this->speed = speed;
    this->color = color;
}

void Bullet::Move()
{
    position.x += speed;
}

void Bullet::Draw() const
{
    DrawCircleV(position, 5, color);
}