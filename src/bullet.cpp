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

    //Collision(player, enemy);
}

bool Bullet::Collision(Enemy& enemy)
{
    // Check if bullet collides with enemy
    float distance = Vector2Distance(position, enemy.enemyPosition);
    return distance < enemy.radius;
}

void Bullet::Draw() const
{
    DrawCircleV(position, 5, color);
}