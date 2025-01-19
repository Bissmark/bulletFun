#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include <raymath.h>
#include <iostream>

Bullet::Bullet(Vector2 position, Vector2 direction, float speed, Color color, Player* player) : position(position), direction(direction), speed(speed), color(color), player(player)
{
    arrowTexture = LoadTexture("src/Spritesheet/Arrow.png");
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

void Bullet::Draw(const Camera2D& camera) const
{
    Vector2 screenBulletPosition = GetWorldToScreen2D(position, camera);
    float angle = atan2f(direction.y, direction.x) * (180.0f / PI);
    DrawTextureEx(arrowTexture, { screenBulletPosition.x, screenBulletPosition.y }, angle, 0.1f, WHITE);
}